#ifndef INSERTDATABASE_H
#define INSERTDATABASE_H

#include "database.h"

class InsertDatabase : public Database
{
    Q_OBJECT

public:
    explicit InsertDatabase(QString connectionName, QObject *parent = 0);
    explicit InsertDatabase(QStringList connectionString, QObject *parent = 0);
signals:

public slots:
    void runQuery();

};

#endif // INSERTDATABASE_H
