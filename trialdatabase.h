#ifndef TRIALDATABASE_H
#define TRIALDATABASE_H

#include "basedatabase.h"

class TrialDatabase : public Database
{
    Q_OBJECT
public:
    explicit TrialDatabase(QString connectionName, QObject *parent = 0);

signals:

public slots:
    void runQuery();

};

#endif // TRIALDATABASE_H
