#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MySortFilterProxyModel(QObject *parent = nullptr);
    ~MySortFilterProxyModel() override;
};

#endif // MYSORTFILTERPROXYMODEL_H
