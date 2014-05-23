#include "databasequeryrequest.h"
#include "databasequery.h"
#include "datastore.h"
#include <QObject>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QMetaObject>
#include <QStack>
#include <QtSql/QSqlDatabase>
#include <QDebug>

int DatabaseQueryRequest::m_nextID(0);

DatabaseQueryRequest::DatabaseQueryRequest(const QStringList &connectString, QObject *parent) :
    QObject(parent),
    m_id(m_nextID++),
    m_database(new Database(connectString, this))
{
    connect(m_database, SIGNAL(queryCompleted()), SLOT(finish()));
    connect(m_database, SIGNAL(resultsReady(DataStore)), SIGNAL(resultsReady(DataStore)));
    connect(m_database, SIGNAL(errorMessageBox(QString,QString)), SIGNAL(errorMessageBox(QString,QString)));
}

DatabaseQueryRequest::DatabaseQueryRequest(QObject *parent) :
    QObject(parent),
    m_id(m_nextID++),
    m_database(0)
{
    connect(m_database, SIGNAL(queryCompleted()), SIGNAL(requestCompleted()));
    connect(m_database, SIGNAL(resultsReady(DataStore)), SIGNAL(resultsReady(DataStore)));
}

DatabaseQueryRequest::~DatabaseQueryRequest()
{
    delete m_database;
    m_database = 0;
    thread()->exit();
    qDebug() << "DQR I'm Gone";
}

//void DatabaseQueryRequest::addConnection(QMetaObject::Connection conn) {
//    m_connections.push(conn);
//}

//void DatabaseQueryRequest::removeConnection() {
////    qDebug() << "removeConnection";
//    if (m_connections.count() > 0) {
//        disconnect(m_connections.pop());
//    }
////    qDebug() << "removed";
//}

void DatabaseQueryRequest::setDatabase(Database *base) {
    if (base && (m_database == 0)) {
        m_database = base;
        connect( m_database, SIGNAL(resultsReady(DataStore)), SIGNAL(resultsReady(DataStore)) );

    }
}

void DatabaseQueryRequest::setQueryString(const QString &string) {
    if (m_database != 0) {
        m_database->setQueryString(string);
    }
}

void DatabaseQueryRequest::setHash(const bool flag) {
    if (m_database != 0) {
        m_database->setHash(flag);
    }
}

void DatabaseQueryRequest::start()
{
    qDebug() << "dbq start";
    if (m_database) {
        //            emit queryStatus(DatabaseQuery::Running, m_currentIndex);
        m_database->runQuery();
    }
}

void DatabaseQueryRequest::finish()
{
    qDebug() << "dbq finish";
    emit requestCompleted();
    deleteLater();
}
