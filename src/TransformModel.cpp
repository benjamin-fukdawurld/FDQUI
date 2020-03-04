#include "include/FDQUI/TransformModel.h"

TransformModel::TransformModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_transform(nullptr)
{

}

QModelIndex TransformModel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return createIndex(row, column, reinterpret_cast<void*>(m_transform));
    }
}

int TransformModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
        return NumberOfFields;

    return 0;
}

int TransformModel::columnCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
        return 1;

    return 0;
}

FD3D::Transform *TransformModel::getTranfsorm()
{
    return m_transform;
}

const FD3D::Transform *TransformModel::getTranfsorm() const
{
    return m_transform;
}

void TransformModel::setTranfsorm(FD3D::Transform *transform)
{
    emit beginResetModel();
    m_transform = transform;
    emit endResetModel();
}
