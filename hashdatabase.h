#ifndef HASHDATABASE_H
#define HASHDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QHash>
#include <QStringList>
#include "database.h"

class QSqlQuery;

class HashDatabase : public Database
{
    Q_OBJECT
public:
    explicit HashDatabase(QString connectionName = QString(), QObject *parent = 0);

//signals:
//    void queryCompleted();

public slots:
    virtual void runQuery() = 0;

protected:

};

#endif // HASHDATABASE_H
