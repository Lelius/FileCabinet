#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QFileSystemModel>
#include <QFileInfo>
#include <QSortFilterProxyModel>
#include <QVariant>

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MySortFilterProxyModel(QObject *parent = 0);
    virtual ~MySortFilterProxyModel();

protected:
    bool lessThan(const QModelIndex &, const QModelIndex &) const;
};

#endif // MYSORTFILTERPROXYMODEL_H
