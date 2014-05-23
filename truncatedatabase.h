#ifndef TRUNCATEDATABASE_H
#define TRUNCATEDATABASE_H

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include "database.h"

class TruncateDatabase : public Database
{
    Q_OBJECT
public:
    explicit TruncateDatabase(QString connectionName, QObject *parent = 0);
    explicit TruncateDatabase(QStringList connectionString = QStringList(), QObject *parent = 0);

signals:

public slots:
    void runQuery();

};

#endif // TRUNCATEDATABASE_H
