#include <FDQUI/VectorModel.h>

using namespace FDQUI;

void VectorModel::unsetVector() { setValues(nullptr, 0, 0); }



QModelIndex RowVectorProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid())
        return QModelIndex();

    auto *model = static_cast<VectorModel*>(sourceModel());
    if(model == nullptr)
        return QModelIndex();


    return createIndex(row, column, model->getValues());
}

QModelIndex RowVectorProxyModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int RowVectorProxyModel::rowCount(const QModelIndex &parent) const
{
    if(sourceModel() == nullptr)
        return 0;

    return sourceModel()->columnCount(parent);
}

int RowVectorProxyModel::columnCount(const QModelIndex &parent) const
{
    if(sourceModel() == nullptr)
        return 0;

    return sourceModel()->rowCount(parent);
}

QVariant RowVectorProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(sourceModel() == nullptr)
        return QVariant();

    return sourceModel()->headerData(section,
                                     (orientation == Qt::Vertical ? Qt::Horizontal : Qt::Vertical),
                                     role);
}

QModelIndex RowVectorProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if(sourceModel() == nullptr)
        return QModelIndex();

    return index(sourceIndex.column(), sourceIndex.row(), sourceIndex.parent());
}

QModelIndex RowVectorProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if(sourceModel() == nullptr)
        return QModelIndex();

    return index(proxyIndex.column(), proxyIndex.row(), proxyIndex.parent());
}
