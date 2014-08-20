#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <QObject>
#include <QAction>
#include <QMetaObject>
#include <QtSql/QSqlDatabase>
#include <QFile>
#include <QList>
#include <QStack>
#include <QPair>
#include <QDebug>
#include "database.h"
#include "datastore.h"

class DatabaseQueryRequest;
typedef QList<DatabaseQueryRequest *> DatabaseQueryRequestList;
class DatabaseQuery : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseQuery(QObject *parent = 0);
    virtual ~DatabaseQuery();

public:
    enum RunType { Join, Query, Insert, None };
    enum Status { Idle, Started, Running, Finished, NoStatus };
    RunType runType();
    bool isValid() { return false; }
    DatabaseQueryRequest *addQueryRequest(const QStringList &connectString,
                                          const QString &queryString,
                                          bool isHashed = false);

signals:
    void logStatus(const QString& msg);
    void resultsReady(DataStore base);
    void started();
    void requestsCleared();
    void queryComplete();
    void errorMessageBox(const QString &title, const QString &text);

public slots:
    void start();
    void statusChanged(DatabaseQuery::Status, int i = 0);
    void setRunType(RunType type) { if (type <= None) m_runType = type; }
    void threadFinished();
    bool isStarted();
    void finish();
    void finishQuery();
    void addResult(DataStore result);

private:

    void runQuery();
    void sendResults();
    void runJoin();

private:
    DatabaseQueryRequestList m_requests;
    DataStoreList m_results;
    RunType m_runType;
    int m_currentIndex;

private:
    void addRequest(DatabaseQueryRequest *request);
    DatabaseQueryRequest *takeRequest();
    void clearRequest(DatabaseQueryRequest *request);
    void clearRequests();
    void clearResults();

    DataStore takeResult();
    //    void clearResults();
};

#endif // DATABASEQUERY_H
