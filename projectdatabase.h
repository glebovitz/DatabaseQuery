#ifndef PROJECTSDATABASE_H
#define PROJECTSDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QHash>
#include <QStringList>
#include "hashdatabase.h"

//class QSqlQuery;
//typedef QHash<int, QStringList> DataHash;

class ProjectDatabase : public HashDatabase
{
    Q_OBJECT
public:
    explicit ProjectDatabase(QString connectionName = QString(), QObject *parent = 0);
    //DataHash getHashTable() { return m_hashTable; }

//signals:
//    void queryCompleted();

public slots:
    void runQuery();

//private:
//    DataHash m_hashTable;
};

#endif // PROJECTSDATABASE_H
