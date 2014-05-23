#ifndef SALESFORCEDATABASE_H
#define SALESFORCEDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QHash>
#include <QStringList>
#include "hashdatabase.h"

class SalesforceDatabase : public Database
{
    Q_OBJECT
public:
    explicit SalesforceDatabase(QString connectionName = QString(), QObject *parent = 0);
    explicit SalesforceDatabase(QStringList connectionString = QStringList(), QObject *parent = 0);
};

#endif // SALESFORCEDATABASE_H
