#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QMessageBox>
#include <QDate>
#include "database.h"
#include "defaults.h"

// =========================================================
// Database
// =========================================================

static QString queryString;
static QString queryName="Query %1";

Database::Database(QString connectionName, QObject *parent) :
    QObject(parent),
    m_database(0),
    m_port(0),
    m_connectionName(connectionName)
{
    if (!connectionName.isEmpty()) {
        openDatabase();
    }
}

Database::Database(QStringList connectionString, QObject *parent) :
    QObject(parent),
    m_database(0),
    m_port(0)
{
    if (!connectionString.isEmpty()) {
        setConnectionName(connectionString.takeFirst());
        openDatabase(connectionString);
    }
}

Database::~Database()
{
    QString name = m_database->connectionName();
    if (m_database->isOpen()) {
        m_database->close();
    }
    delete m_database;
    QSqlDatabase::removeDatabase(name);
}

void Database::openDatabase(const QStringList &connectionList) {
    if (m_database == 0) {
        m_database = new QSqlDatabase;
        if (QSqlDatabase::contains(m_connectionName)) {
            *m_database = QSqlDatabase::database(m_connectionName);
        } else {
            *m_database = QSqlDatabase::addDatabase("QPSQL", m_connectionName);
        }
        m_database->setConnectOptions("requiressl=true");
    }
    setConnectionString(connectionList);
}

void Database::setConnectionString (const QStringList &list) {
    if (m_database != 0 && list.count() == 5) {
        int index = 0;
        m_database->setHostName(list[index++]);
        m_database->setDatabaseName(list[index++]);
        m_database->setUserName(list[index++]);
        m_database->setPort(list[index++].toInt());
        m_database->setPassword(list[index++]);
    }
}

void Database::setOptions() {

}

void Database::getOptions() {
//    DatabaseDialog *dialog = new DatabaseDialog(this);

//    dialog->setHostName(m_host);
//    dialog->setDatabaseName(m_databaseName);
//    dialog->setUserName(m_user);
//    dialog->setPort(m_port);
//    dialog->setConnectionName(m_connectionName);
//    dialog->setPassword(m_password);

//    connect(dialog, SIGNAL(databaseNameChanged(QString)), SLOT(setDatabaseName(QString)) );
//    connect(dialog, SIGNAL(hostNameChanged(QString)), SLOT(setHostName(QString)) );
//    connect(dialog, SIGNAL(userNameChanged(QString)), SLOT(setUserName(QString)) );
//    connect(dialog, SIGNAL(passwordChanged(QString)), SLOT(setPassword(QString)) );
//    connect(dialog, SIGNAL(portChanged(int)), SLOT(setPort(int)) );
//    dialog->exec();
}

QString Database::formatData(const QVariant &data) {
    QString returnData;
    switch(data.type()) {
    case QVariant::DateTime:
        returnData = data.toDate().toString("MM/dd/yyyy");
        break;
    case QVariant::String:
        returnData = data.toString().remove("\"");
        break;
    default:
        returnData =  data.toString().remove("\"");
        break;
    }
//    qDebug() << returnData;
    return returnData;
}

void Database::setQueryString(QString string) {
    m_queryString = string;
}

void Database::appendQueryString(QString string) {
    m_queryString += string;
}

void Database::runQuery() {
//    qDebug() << m_database->hostName() << m_database->userName() << m_database->password() << m_database->port() << m_database->databaseName();
    if (isValid()) {
//        qDebug() << m_queryString;
        if (m_database->open()) {
            QSqlQuery query(*m_database);
            if (query.exec(m_queryString)) {
                //            qDebug() << m_queryString;
                if (query.isActive()) {
                    int count = query.record().count();
                    qDebug() << count << query.size();
                    for (int i = 0; i < count; i++) {
                        appendHeader(query.record().fieldName(i));
                        appendType(query.record().field(i).type());
                    }
                    // qDebug() << m_dataHeader;
                    for (int row = 0; query.next(); row++) {
                        QStringList list;
                        for (int i = 0; i < count; i++) {
                            list.append(formatData(query.value(i)));
                        }
                        appendData(list);
                    }
                    query.finish();
                }
            } else { emit errorMessageBox(queryName.arg("Exec"), query.lastError().text()); }
            m_database->close();
        } else { emit errorMessageBox(queryName.arg("Open"), m_database->lastError().text()); }
    }
    qDebug() << "DONE";
    emit resultsReady(m_store);
    emit queryCompleted();
}
