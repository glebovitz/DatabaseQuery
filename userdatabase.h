#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QHash>
#include <QStringList>
#include "hashdatabase.h"

//class QSqlQuery;
//typedef QHash<int, QStringList> DataHash;

//class UserDatabase : public HashDatabase
class UserDatabase : public Database
{
    Q_OBJECT
public:
    explicit UserDatabase(QString connectionName = QString(), QObject *parent = 0);
    explicit UserDatabase(QStringList connectionString = QStringList(), QObject *parent = 0);
};
#endif // USERDATABASE_H
