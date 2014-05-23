#include "databasedialog.h"
#include "salesforcedatabase.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QDate>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include <QVariant>
#include <iostream>

SalesforceDatabase::SalesforceDatabase(QString connectionName, QObject *parent) :
    Database(connectionName, parent)
{
}

SalesforceDatabase::SalesforceDatabase(QStringList connectionString, QObject *parent) :
    Database(connectionString, parent)
{
}


