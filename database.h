#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>


#include <QObject>
#include <QSqlDatabase>
#include <QStringList>
#include <QList>
#include <QHash>
#include <QVariant>
#include <QPair>
#include "defaults.h"
#include "datastore.h"

typedef QList<QStringList> DataList;
//typedef QPair<QString,QString> DataSelectItem;
//typedef QList<DataSelectItem> DataSelectList;
typedef QList<QVariant::Type> DataTypeList;
typedef QHash<QString, QStringList> DataHash;

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QString connectionName = QString(), QObject *parent = 0);
    explicit Database(QStringList connectionString = QStringList(), QObject *parent = 0);
    ~Database();

    const DataHash &getHashTable() const { return m_store.dataHash(); }
    const DataList &getDataList() const { return m_store.dataList(); }
    const QStringList &getHeaders() const { return m_store.dataHeaders(); }
    const DataTypeList &getTypes() const { return m_store.typeList(); }
    DataStore getBase() { return m_store; }

    QString connectionName() { return m_connectionName; }
    bool isValid() { return m_database->isValid(); }


signals:
    void queryCompleted();
    void resultsReady(DataStore store);
    void errorMessageBox(const QString &title, const QString &text);

public slots:

    // Database Connection
    void setDatabase(QString name) { m_databaseName = name; }
    void setUser(QString name) { m_user = name; }
    void setPort(int port = 5642) { m_port = port; }
    void setHost(QString name = "localhost") { m_host = name; }
    void setPassword(QString password) { m_password = password; }
    void setConnectionName(QString name) { m_connectionName = name; }
    void setConnectionString (const QStringList &list);

    // Database Query
    void setQueryString(QString string);
    void appendQueryString(QString string);

    // DataStore
    void appendData(const QStringList &list) { m_store.appendData(list); }
    void appendHeader(const QString &str) { m_store.appendHeader(str); }
    void appendType(const DataType &type) { m_store.appendType(type); }
    void setDatalist(const DataList &list) { m_store.setDatalist(list); }
    void setHash(bool flag = true) { m_store.setHash(flag); }
    void setHash(DataHash hash) { m_store.setHash(hash); }
    void setHeader(QStringList list) { m_store.setHeader(list); }
    bool isHash() { return m_store.isHash(); }

    virtual void getOptions();
    virtual void setOptions();
    virtual void runQuery();

protected:
    QSqlDatabase *m_database;
    QSqlQuery *m_query;

    QString m_host;
    QString m_databaseName;
    QString m_user;
    QString m_password;
    int m_port;
    QString m_connectionName;

    DataStore m_store;
    QString m_queryString;

    virtual QString formatData(const QVariant &data);
    void openDatabase(const QStringList &connectionString = QStringList());

};

#endif // DATABASE_H
