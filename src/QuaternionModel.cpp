#include <FDQUI/QuaternionModel.h>

using namespace FDQUI;


glm::quat &QuaternionModel::getQuaternion()
{
    return *reinterpret_cast<glm::quat*>(getValues());
}

const glm::quat &QuaternionModel::getQuaternion() const
{
    return *reinterpret_cast<const glm::quat*>(getValues());
}

void QuaternionModel::setQuaternion(glm::quat &q)
{
    setValues(glm::value_ptr(q), 4, 1);
}

void QuaternionModel::unsetQuaternion() { setValues(nullptr, 0, 0); }



QModelIndex RowQuaternionProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid())
        return QModelIndex();

    auto *model = static_cast<QuaternionModel*>(sourceModel());
    if(model == nullptr)
        return QModelIndex();


    return createIndex(row, column, model->getValues());
}

QModelIndex RowQuaternionProxyModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}



int RowQuaternionProxyModel::rowCount(const QModelIndex &parent) const
{
    if(sourceModel() == nullptr)
        return 0;

    return sourceModel()->columnCount(parent);
}

int RowQuaternionProxyModel::columnCount(const QModelIndex &parent) const
{
    if(sourceModel() == nullptr)
        return 0;

    return sourceModel()->rowCount(parent);
}

QVariant RowQuaternionProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(sourceModel() == nullptr)
        return QVariant();

    return sourceModel()->headerData(section,
                                     (orientation == Qt::Vertical ? Qt::Horizontal : Qt::Vertical),
                                     role);
}

QModelIndex RowQuaternionProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if(sourceModel() == nullptr)
        return QModelIndex();

    return index(sourceIndex.column(), sourceIndex.row(), sourceIndex.parent());
}

QModelIndex RowQuaternionProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if(sourceModel() == nullptr)
        return QModelIndex();

    return index(proxyIndex.column(), proxyIndex.row(), proxyIndex.parent());
}
