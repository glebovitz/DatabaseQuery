#include "datastore.h"
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QDate>
#include <QTime>
#include "defaults.h"


DataStore::DataStore(bool hashFlag)
    : m_hashFlag(hashFlag),
      m_id(QTime::currentTime())
{
}

void DataStore::setHash (DataHash hash) {
    if (!hash.isEmpty()) {
        m_hashTable = hash;
        m_hashFlag = true;
    }
}

void DataStore::appendData(const QStringList &list) {
    m_dataList.append(list);
    if (isHash()) {
        if (!list[0].isEmpty()) {
            m_hashTable[list[0]] = list;
        }
    }
}

bool DataStore::operator <(const DataStore &store) const {
    return m_id < store.m_id;
}
