#ifndef SORTPROXYMODEL_H
#define SORTPROXYMODEL_H

#include <QSortFilterProxyModel>

class SortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SortProxyModel(QObject *parent = 0);

signals:

public slots:

protected:
    bool lessThan(const QModelIndex & left, const QModelIndex & right) const;

};

#endif // SORTPROXYMODEL_H
