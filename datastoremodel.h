#ifndef DATASTOREMODEL_H
#define DATASTOREMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include "database.h"
#include "datastore.h"

class DataStoreModel : public QAbstractTableModel
{
    Q_OBJECT

private:
//    DataList m_dataList;
//    DataTypeList m_typeList;
//    QStringList m_headers;

public:
    explicit DataStoreModel(QObject *parent = 0);
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual int	columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex & index) const { Q_UNUSED(index); return QModelIndex(); }

public:
    QString toString();
    const DataStore &dataStore() const { return m_store; }
    DataTypeList typeList() { return m_store.typeList(); }
    DataList dataList() { return m_store.dataList(); }
    QStringList dataHeader() { return m_store.dataHeaders(); }

signals:

public slots:
    void setDataStore(DataStore base);

private:
    DataStore m_store;
};

#endif // DATASTOREMODEL_H
