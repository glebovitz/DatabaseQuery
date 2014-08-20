#ifndef DATABASEQUERYREQUEST_H
#define DATABASEQUERYREQUEST_H

#include <QObject>
#include <QAction>
#include <QMetaObject>
#include <QtSql/QSqlDatabase>
#include <QFile>
#include <QList>
#include <QStack>
#include <QPair>
#include <QDebug>
#include <QThread>
#include "database.h"
#include "datastore.h"
#include "databasequery.h"

class DatabaseQueryRequest : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseQueryRequest(const QStringList &connectString, QObject *parent = 0);
    explicit DatabaseQueryRequest(QObject *parent = 0);
    ~DatabaseQueryRequest();

private: // Types
    typedef QStack<QMetaObject::Connection> ConnectionList;
    typedef QList<QAction *> ActionList;
    typedef QPair<QStringList, QString> QueryDatabase;
    typedef QList<QueryDatabase> QueryDatabaseList;

signals:
//    void queryStatus(DatabaseQuery::Status status, int idx = 0);
    void requestCompleted(int idx = 0);
    void resultsReady(DataStore results);
    void errorMessageBox(const QString &title, const QString &text);

public:
    bool hasDatabases() { return m_currentIndex != 0; }
    Database *database() { return m_database; }
    int id() { return m_id; }

public slots:
    void setDatabase(Database *database);
    void setQueryString(const QString &queryString);
    void setHash(const bool flag);
    void start();
    void finish();
//    void addDatabase(Database *database);
    void removeDatabase() {}

//    void addQueries(const QueryDatabaseList &list, bool isHashed = false);

//    void addConnection(QMetaObject::Connection);
//    void removeConnection();

//    void importDatabase();

private: // Properties
    int m_id;
    Database *m_database;
    ConnectionList m_connections;
    int m_currentIndex;
    bool m_isStarted;
    static int m_nextID;

//    ActionList m_actionList;

//    DataHash m_dataHash;
//    DataList m_dataList;
//    QStringList m_dataHeaders;
//    DataTypeList m_dataTypes;

//    QString m_savedFileName;

private: // methods
};


#endif // DATABASEQUERYREQUEST_H
