#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QMessageBox>
#include "licensedatabase.h"
#include "basedatabase.h"
#include "defaults.h"
#include <QDate>

LicenseDatabase::LicenseDatabase(QString connectionName, QObject *parent) :
    Database(connectionName, parent)
{
}

LicenseDatabase::LicenseDatabase(QStringList connectionString, QObject *parent) :
    Database(connectionString, parent)
{
}
