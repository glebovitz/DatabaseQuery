#include "truncatedatabase.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QMessageBox>


static QString queryString = QString("TRUNCATE TABLE ONLY \"public\".\"salesforce\" ");

static QString queryName = QString("Truncate Query %1");

TruncateDatabase::TruncateDatabase(QString connectionName, QObject *parent) :
    Database(connectionName, parent)
{
    setQueryString(queryString);
}

TruncateDatabase::TruncateDatabase(QStringList connectionString, QObject *parent) :
    Database(connectionString, parent)
{
    setQueryString(queryString);
}

void TruncateDatabase::runQuery() {
    // qDebug() << dbase.hostName() << dbase.userName() << dbase.password() << dbase.port() << dbase.databaseName();
    qDebug() << "Starting Truncate Salesforce" << connectionName();
    if (dbase.open()) {
        QSqlQuery query(dbase);
        qDebug() << queryString;
        if (!query.exec(m_queryString)) {
            QMessageBox::warning(0, queryName.arg("Open"), query.lastError().text());
        }
        qDebug() << "DONE" << connectionName();
        dbase.close();
        emit queryCompleted();
    } else { QMessageBox::warning(0, queryName.arg("Open"), dbase.lastError().text()); }
}
