#include "mysortfilterproxymodel.h"

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

MySortFilterProxyModel::~MySortFilterProxyModel()
{

}

bool MySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex& right) const
{
    QFileSystemModel *fileSystemModel = static_cast<QFileSystemModel *>(sourceModel());
    QFileInfo leftFileInfo = fileSystemModel->fileInfo(left);
    QFileInfo rightFileInfo = fileSystemModel->fileInfo(right);

    if (leftFileInfo.isDir() && rightFileInfo.isDir()) {
        return leftFileInfo.fileName() < rightFileInfo.fileName();
    }
    else if (leftFileInfo.isDir() && (!rightFileInfo.isDir())) {
        return true;
    }
    else if ((!leftFileInfo.isDir()) && rightFileInfo.isDir()) {
        return false;
    }
    else if ((!leftFileInfo.isDir()) && (!rightFileInfo.isDir())) {
        return leftFileInfo.fileName() < rightFileInfo.fileName();
    }

    return true;
}
