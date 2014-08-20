#include "datastore.h"
#include "datastoremodel.h"

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QStringList>
#include <QString>
#include <QDebug>

DataStoreModel::DataStoreModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

QVariant DataStoreModel::data(const QModelIndex & index, int role) const {
    if (!m_store.dataList().isEmpty() && index.isValid()) {
        if (role == Qt::DisplayRole) {
//            QStringList stringList(m_dataList[index.row()]);
            const QStringList stringList(m_store.dataList()[index.row()]);
            if (index.column() < stringList.count()) {

                switch (m_store.typeList()[index.column()]) {
                case QVariant::Int:
                    return stringList.value(index.column()).toInt();
                    break;
                case QVariant::UInt:
                    return stringList.value(index.column()).toUInt();
                    break;
                case QVariant::LongLong:
                    return stringList.value(index.column()).toLongLong();
                    break;
                case QVariant::ULongLong:
                    return stringList.value(index.column()).toULongLong();
                    break;
                default:
                    return stringList.value(index.column());
                    break;
                }
            }
        }
    }
    return (QVariant());
}

QVariant DataStoreModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // Q_UNUSED(orientation);
    if (!m_store.dataHeaders().isEmpty() && (orientation == Qt::Horizontal)) {
        if (role == Qt::DisplayRole) {
            QString head = m_store.dataHeaders()[section];
            return QVariant(head);
        }
    }
    return (QVariant());
}


int	DataStoreModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return(m_store.dataList().count());

}

int	DataStoreModel::columnCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    int count = m_store.dataHeaders().count();
    return(count);

}

void DataStoreModel::setDataStore(DataStore base) {
    beginResetModel();
    m_store = base;
    endResetModel();
}
