#include "databasequery.h"
#include "databasequeryrequest.h"
#include "datastore.h"
#include <QObject>
#include <QAction>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QMetaObject>
#include <QStack>
#include <QThread>
#include <QtSql/QSqlDatabase>
#include <QDebug>

DatabaseQuery::DatabaseQuery(QObject *parent)
    : QObject(parent),
      m_runType(Query)
{

}

DatabaseQuery::~DatabaseQuery()
{
    clearRequests();
    clearResults();
}

DatabaseQueryRequest *DatabaseQuery::addQueryRequest(const QStringList &connectString,
                             const QString &queryString, bool isHashed) {
        DatabaseQueryRequest *request = new DatabaseQueryRequest(connectString);
        request->setQueryString(queryString);
        request->setHash(isHashed);
        m_requests.append(request);
        return request;
}

void DatabaseQuery::start() {
    emit resultsReady(DataStore());
    while (m_requests.count() > 0) {
        runQuery();
    }
}

bool DatabaseQuery::isStarted() {
//    if (m_request)
//        return m_request->hasDatabases();
//    else
        return false;
}

void DatabaseQuery::finish() {
    DatabaseQueryRequest *request = qobject_cast<DatabaseQueryRequest*>(QObject::sender());
    if (request) {
        request->deleteLater();
    }
}

void DatabaseQuery::threadFinished()
{
    QThread *thread = qobject_cast<QThread *>(QObject::sender());
    qDebug() << "Thread " << thread << " finished";
    if (thread) {
        thread->deleteLater();
    }
}

DatabaseQuery::RunType DatabaseQuery::runType()
{
        return m_runType;
}

void DatabaseQuery::addRequest(DatabaseQueryRequest *request) {
    if (request) {
        m_requests.append(request);
    }
}

DatabaseQueryRequest* DatabaseQuery::takeRequest() {
    if (!m_requests.isEmpty()) {
        return m_requests.takeFirst();
    }
    return 0;
}

void DatabaseQuery::clearRequest(DatabaseQueryRequest *request) {
    if (request) {
        request->deleteLater();
    }
}

void DatabaseQuery::clearRequests() {
    //enableActions(flag);
    while (!m_requests.isEmpty()) {
        clearRequest(m_requests.takeFirst());
    }
    emit requestsCleared();
}


void DatabaseQuery::addResult(DataStore result)
{
    //DatabaseQueryRequest *request = qobject_cast<DatabaseQueryRequest*>(QObject::sender());
    m_results.append(result);
}

DataStore DatabaseQuery::takeResult() {
    if (!m_results.isEmpty()) {
        return m_results.takeFirst();
    }
    return DataStore();
}

void DatabaseQuery::clearResults() {
    //enableActions(flag);
    m_results.clear();
    emit requestsCleared();
}

void DatabaseQuery::statusChanged(Status status, int i) {
    switch(status) {
    case Idle:
        logStatus(QString("Idle DB %1").arg(i));
        break;
    case Started:
        logStatus(QString("Started DB %1").arg(i));
        break;
    case Running:
        logStatus(QString("Running DB %1").arg(i));
        break;
    case Finished:
        logStatus(QString("Finished DB %1").arg(i));
        break;
    default:
        break;
    }
}


void DatabaseQuery::runQuery() {
    DatabaseQueryRequest *request = takeRequest();
    if (request) {
        QThread *thread = new QThread();
        connect(thread, SIGNAL(finished()), SLOT(threadFinished()));
        thread->start();
        request->moveToThread(thread);
        connect( request, SIGNAL(requestCompleted()), SLOT(finishQuery()) );
        connect( request, SIGNAL(resultsReady(DataStore)), SLOT(addResult(DataStore)) );
        connect( request, SIGNAL(errorMessageBox(QString,QString)), SIGNAL(errorMessageBox(QString,QString)) );
        QMetaObject::invokeMethod(request, "start", Qt::QueuedConnection);
    }
}

void DatabaseQuery::finishQuery() {
    //    removeConnection();
    //    emit queryStatus(DatabaseQuery::Finished, m_currentIndex);
    qDebug() << "finishedQuery";
    int count = m_results.count();
    if (count > 0) {
        switch(runType()) {
        case Join:
            runJoin();
            break;
        case Insert:
        case Query:
            qDebug() << "Query";
            sendResults();
            break;
        default:
            break;
        }
    } else {
        finish();
    }
}

void DatabaseQuery::sendResults() {
    while (m_results.count() > 0) {
        emit resultsReady(m_results.takeFirst());
    }
}

void DatabaseQuery::runJoin() {
    qDebug() << "Run Join";
    if (m_results.count() == 2) {
        //qSort(m_results);
        DataStore firstBase = m_results.takeFirst();
        DataStore secondBase = m_results.takeFirst();

        if (firstBase.rowCount() > 0 && secondBase.rowCount() > 0) {
            // m_dataHeaders contains the imported salesforce IDs
            DataStore joinResult;
            joinResult.setHeader(firstBase.dataHeaders() + secondBase.dataHeaders().mid(1));
            joinResult.setTypes( firstBase.typeList() + secondBase.typeList().mid(1));
            QListIterator<QStringList> index(firstBase.dataList());
            for (int row = 0; index.hasNext(); row++) {
                QStringList list = index.next();
                if (! list.empty()) {
                    QStringList secondList = secondBase.dataHash()[list.first()].mid(1);
                    if (! secondList.isEmpty()) {
                        // m_dataHash will look up the imported salesforce IDs.
                        list += secondList;
                        joinResult.appendData(list);
                    }
                }
            }
            resultsReady(joinResult);
        }
    }
}
