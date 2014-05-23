#ifndef LICENSEDATABASE_H
#define LICENSEDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QStringList>
#include <QList>
#include "defaults.h"
#include "database.h"

typedef QList<QStringList> LicenseList;

//class BillingTable {

//public:
//    QStringList header;
//    BillingList list;
//};

class LicenseDatabase : public Database
{
    Q_OBJECT
public:
    explicit LicenseDatabase(QString connectionName = QString(), QObject *parent = 0);
    explicit LicenseDatabase(QStringList connectionString = QStringList(), QObject *parent = 0);

};

#endif // LICENSEDATABASE_H
