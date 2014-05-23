#ifndef INSERTSALESFORCEDB_H
#define INSERTSALESFORCEDB_H

#include "importsftable.h"
#include "database.h"

class ImportSFTable : public Database
{
    Q_OBJECT

public:
    explicit ImportSFTable(QString connectionName, QObject *parent = 0);
    explicit ImportSFTable(QStringList connectionString, QObject *parent = 0);
signals:

public slots:
    void runQuery();

};

#endif // INSERTSALESFORCEDB_H
