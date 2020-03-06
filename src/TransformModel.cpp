#include "include/FDQUI/TransformModel.h"

TransformModel::TransformModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_transform(nullptr)
{

}

QModelIndex TransformModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!m_transform)
        return QModelIndex();

    if(!parent.isValid())
    {
        return createIndex(row, column, static_cast<quintptr>(InternalId::Transform));
    }


    switch(static_cast<InternalId>(parent.internalId()))
    {
        case InternalId::Transform:
        switch(static_cast<TransformField>(row))
        {
            case TransformField::Position:
            return createIndex(row, column, static_cast<quintptr>(InternalId::Position));

            case TransformField::Scale:
            return createIndex(row, column, static_cast<quintptr>(InternalId::Scale));

            case TransformField::Rotation:
            return createIndex(row, column, static_cast<quintptr>(InternalId::Scale));
        }
        break;
    }

    if(parent.internalPointer() == ptr)
    {
        switch(static_cast<TransformField>(parent.row()))
        {
            case TransformField::Position:
                ptr = reinterpret_cast<void*>(&m_transform->getPosition());
            break;

            case TransformField::Scale:
                ptr = reinterpret_cast<void*>(&m_transform->getScale());
            break;

            case TransformField::Rotation:
                ptr = reinterpret_cast<void*>(&m_transform->getRotation());
            break;

            case TransformField::Matrice:
                ptr = const_cast<void*>(reinterpret_cast<const void*>(&m_transform->getMatrix()));
            break;

            case TransformField::IsUpToDate:
                // As We cannot get the address of the boolean we set it to the last byte of the Transform structure
                ptr = (reinterpret_cast<char*>(m_transform) + sizeof(FD3D::Transform) - 1);
            break;
        }

        return createIndex(row, column, ptr);
    }

    if(parent.internalPointer() < (reinterpret_cast<char*>(m_transform) + sizeof(FD3D::Transform)))
    {

    }

    return QModelIndex();
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
