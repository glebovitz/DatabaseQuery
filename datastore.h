#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QHash>
#include <QTime>
#include <QVariant>
#include <QPair>
#include "defaults.h"

typedef QList<QStringList> DataList;
typedef QVariant::Type DataType;
typedef QList<DataType> DataTypeList;
typedef QHash<QString, QStringList> DataHash;

class DataStore
{
public:
    explicit DataStore(bool hashFLag = false);
    virtual ~DataStore() {}

public: // getter methods
    const DataHash &dataHash() const { return m_hashTable; }
    const DataList &dataList() const { return m_dataList; }
    const QStringList &dataHeaders() const { return m_dataHeader; }
    const DataTypeList &typeList() const { return m_typeList; }
    int rowCount() const { return m_dataList.count(); }
    bool isValid() { return rowCount() != 0; }
    bool isHash() { return m_hashFlag; }
    const QStringList &value(QString key) { return m_hashTable[key]; }
    const QTime id() const { return m_id; }

public:
    void setDatalist(const DataList &list) { m_dataList = list; }
    void setTypes(DataTypeList typeList) { m_typeList = typeList; }
    void setHash(bool flag = true) { m_hashFlag = flag; }
    void setId(QTime id) { m_id = id; }
    void setHash(DataHash hash);
    void setHeader(QStringList list) { m_dataHeader = list; }

    void appendData(const QStringList &list);
    void appendHeader(const QString &str) { m_dataHeader.append(str); }
    void appendType(const DataType &type) { m_typeList.append(type); }

    virtual void getOptions() {}
    virtual void setOptions() {}
    virtual void runQuery()   {}

    bool operator<(const DataStore &store) const;

private:
    DataList m_dataList;
    DataTypeList m_typeList;
    QStringList m_dataHeader;
    DataHash m_hashTable;
    bool m_hashFlag;
    QTime m_id;
};

typedef QList<DataStore> DataStoreList;

Q_DECLARE_METATYPE(DataStore)

#endif // DATASTORE_H
