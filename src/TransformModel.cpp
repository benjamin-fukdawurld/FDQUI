#include <FDQUI/Model/TransformModel.h>

FDQUI::TransformModel::TransformModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_transform(nullptr)
{

}

QModelIndex FDQUI::TransformModel::index(int row, int column, const QModelIndex &parent) const
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
                return createIndex(row, column, static_cast<quintptr>(InternalId::Rotation));

                case TransformField::Matrix:
                return createIndex(row, column, static_cast<quintptr>(InternalId::Matrix));

                case TransformField::IsUpToDate:
                return createIndex(row, column, static_cast<quintptr>(InternalId::IsUpToDate));
            }
        break;

        case InternalId::Position:
            if(column != 0)
                return QModelIndex();

            switch(row)
            {
                case 0:
                return createIndex(row, column, static_cast<quintptr>(InternalId::PositionX));

                case 1:
                return createIndex(row, column, static_cast<quintptr>(InternalId::PositionY));

                case 2:
                return createIndex(row, column, static_cast<quintptr>(InternalId::PositionZ));

                default:
                return QModelIndex();
            }

        case InternalId::Scale:
            if(column != 0)
                return QModelIndex();

            switch(row)
            {
                case 0:
                return createIndex(row, column, static_cast<quintptr>(InternalId::ScaleX));

                case 1:
                return createIndex(row, column, static_cast<quintptr>(InternalId::ScaleY));

                case 2:
                return createIndex(row, column, static_cast<quintptr>(InternalId::ScaleZ));

                default:
                return QModelIndex();
            }

        case InternalId::Rotation:
            if(column != 0)
                return QModelIndex();

            switch(row)
            {
                case 0:
                return createIndex(row, column, static_cast<quintptr>(InternalId::RotationW));

                case 1:
                return createIndex(row, column, static_cast<quintptr>(InternalId::RotationX));

                case 2:
                return createIndex(row, column, static_cast<quintptr>(InternalId::RotationY));

                case 3:
                return createIndex(row, column, static_cast<quintptr>(InternalId::RotationZ));

                default:
                return QModelIndex();
            }

        case InternalId::Matrix:
            if(column < 0 || column >= 16 || row < 0 || row >= 16)
                return QModelIndex();

        return createIndex(row, column,
                           static_cast<quintptr>(InternalId::Matrix) + 1
                           + static_cast<quintptr>(row * 4 + column));

        default:
            return QModelIndex();

    }

    return QModelIndex();
}

QModelIndex FDQUI::TransformModel::parent(const QModelIndex &index) const
{
    if(!m_transform)
        return QModelIndex();

    if(!index.isValid())
        return QModelIndex();

    if(index.internalId() > static_cast<quintptr>(InternalId::IsUpToDate))
        return QModelIndex();

    switch(index.internalId())
    {
        case static_cast<quintptr>(InternalId::Transform):
        return QModelIndex();

        case static_cast<quintptr>(InternalId::Position):
        case static_cast<quintptr>(InternalId::Scale):
        case static_cast<quintptr>(InternalId::Rotation):
        case static_cast<quintptr>(InternalId::Matrix):
        case static_cast<quintptr>(InternalId::IsUpToDate):
        return createIndex(0, 0, static_cast<quintptr>(InternalId::Transform));

        case static_cast<quintptr>(InternalId::PositionX):
        case static_cast<quintptr>(InternalId::PositionY):
        case static_cast<quintptr>(InternalId::PositionZ):
        return createIndex(0, 0, static_cast<quintptr>(InternalId::Position));

        case static_cast<quintptr>(InternalId::ScaleX):
        case static_cast<quintptr>(InternalId::ScaleY):
        case static_cast<quintptr>(InternalId::ScaleZ):
        return createIndex(1, 0, static_cast<quintptr>(InternalId::Scale));

        case static_cast<quintptr>(InternalId::RotationX):
        case static_cast<quintptr>(InternalId::RotationY):
        case static_cast<quintptr>(InternalId::RotationZ):
        case static_cast<quintptr>(InternalId::RotationW):
        return createIndex(2, 0, static_cast<quintptr>(InternalId::Rotation));

        default:
        return createIndex(3, 0, static_cast<quintptr>(InternalId::Matrix));
    }
}

int FDQUI::TransformModel::rowCount(const QModelIndex &parent) const
{
    if(!m_transform)
        return 0;

    if(!parent.isValid())
        return 1;

    if(parent.internalId() == static_cast<quintptr>(InternalId::Transform))
        return NumberOfFields;

    if(parent.internalId() == static_cast<quintptr>(InternalId::Position)
       || parent.internalId() == static_cast<quintptr>(InternalId::Scale))
        return 3;

    if(parent.internalId() == static_cast<quintptr>(InternalId::Rotation)
       || parent.internalId() == static_cast<quintptr>(InternalId::Matrix))
        return 4;

    if(parent.internalId() == static_cast<quintptr>(InternalId::IsUpToDate))
        return 0;

    return 0;
}

int FDQUI::TransformModel::columnCount(const QModelIndex &parent) const
{
    if(!m_transform)
        return 0;

    if(!parent.isValid())
        return 1;

    if(parent.internalId() == static_cast<quintptr>(InternalId::Matrix))
        return 4;

    return 1;
}

bool FDQUI::TransformModel::hasChildren(const QModelIndex &parent) const
{
    if(!m_transform)
        return false;

    if(!parent.isValid())
        return true;

    if(parent.internalId() == static_cast<quintptr>(InternalId::Transform)
       || parent.internalId() == static_cast<quintptr>(InternalId::Position)
       || parent.internalId() == static_cast<quintptr>(InternalId::Scale)
       || parent.internalId() == static_cast<quintptr>(InternalId::Rotation)
       || parent.internalId() == static_cast<quintptr>(InternalId::Matrix))
        return true;

    return false;
}

QVariant FDQUI::TransformModel::data(const QModelIndex &index, int role) const
{
    if(m_transform == nullptr || !index.isValid()
       || index.internalId() > static_cast<quintptr>(InternalId::IsUpToDate))
        return QVariant();

    if(index.internalId() == static_cast<quintptr>(InternalId::Transform))
    {
        if(role == Qt::DisplayRole || role == Qt::ToolTipRole
           || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Transform");
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::Position))
    {
        if(role == Qt::DisplayRole || role == Qt::ToolTipRole
           || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Position");
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::PositionX))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Position.x");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getPosition().x;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::PositionY))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Position.y");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getPosition().y;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::PositionZ))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Position.z");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getPosition().z;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::Scale))
    {
        if(role == Qt::DisplayRole || role == Qt::ToolTipRole
           || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return "Scale";
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::ScaleX))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Scale.x");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getScale().x;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::ScaleY))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Scale.y");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getScale().y;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::ScaleZ))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Scale.z");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getScale().z;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::Rotation))
    {
        if(role == Qt::DisplayRole || role == Qt::ToolTipRole
           || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return "Rotation";
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::RotationX))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Rotation.x");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getRotation().x;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::RotationY))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Rotation.y");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getRotation().y;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::RotationZ))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Rotation.z");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getRotation().z;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::RotationW))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Rotation.w");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getRotation().w;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::IsUpToDate))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Is matrix up to date");

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return tr("IsUpToDate");

        if(role == Qt::CheckStateRole)
            return m_transform->isUptoDate() ? Qt::Checked : Qt::Unchecked;
    }

    if(index.internalId() == static_cast<quintptr>(InternalId::Matrix))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Model transformation matrix");

        if(role == Qt::DisplayRole)
            return tr("Matrix");
    }

    if(index.internalId() > static_cast<quintptr>(InternalId::Matrix))
    {
        if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole || role == Qt::StatusTipRole)
            return tr("Model transformation matrix[%1][%2]").arg(index.row(), index.column());

        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return m_transform->getMatrixPtr()[index.row() + index.column() * 4];
    }

    return QVariant();
}

bool FDQUI::TransformModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(m_transform == nullptr || !index.isValid()
       || index.internalId() > static_cast<quintptr>(InternalId::IsUpToDate))
        return false;

    if(index.internalId() == static_cast<quintptr>(InternalId::Transform)
       || index.internalId() == static_cast<quintptr>(InternalId::Position)
       || index.internalId() == static_cast<quintptr>(InternalId::Scale)
       || index.internalId() == static_cast<quintptr>(InternalId::Rotation)
       || index.internalId() == static_cast<quintptr>(InternalId::Matrix))
        return false;

    if(index.internalId() == static_cast<quintptr>(InternalId::PositionX))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getPosition().x = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::PositionY))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getPosition().y = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::PositionZ))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getPosition().z = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::ScaleX))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getScale().x = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::ScaleY))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getScale().y = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::ScaleZ))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getScale().z = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::RotationX))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getRotation().x = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::RotationY))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getRotation().y = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::RotationZ))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getRotation().z = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::RotationW))
    {
        if(role == Qt::EditRole)
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok)
                return false;

            m_transform->getRotation().w = f;
            dataChanged(index, index);
            return true;
        }
    }
    else if(index.internalId() == static_cast<quintptr>(InternalId::IsUpToDate))
    {
        if(role == Qt::CheckStateRole)
        {
            bool b = value == Qt::Checked;
            if(b == m_transform->isUptoDate())
                return true;

            if(b)
                m_transform->update();
            else
                m_transform->invalidate();

            dataChanged(index, index);
            QModelIndex matrixIndex = createIndex(3, 0, static_cast<quintptr>(InternalId::Matrix));
            dataChanged(this->index(0, 0, matrixIndex), this->index(3, 3, matrixIndex));
            return true;
        }
    }

    // Matrix is not updatable outside of the transform

    return false;
}

Qt::ItemFlags FDQUI::TransformModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result =
            Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled;

    if(index.internalId() == static_cast<quintptr>(InternalId::Transform)
       || index.internalId() == static_cast<quintptr>(InternalId::Position)
       || index.internalId() == static_cast<quintptr>(InternalId::Scale)
       || index.internalId() == static_cast<quintptr>(InternalId::Rotation)
       || index.internalId() == static_cast<quintptr>(InternalId::Matrix))
        return result;

    if(index.internalId() > static_cast<quintptr>(InternalId::Matrix)
       && index.internalId() != static_cast<quintptr>(InternalId::IsUpToDate))
        return result | Qt::ItemNeverHasChildren;

    if(index.internalId() == static_cast<quintptr>(InternalId::IsUpToDate))
        result |= Qt::ItemIsUserCheckable;
    else
        result |= Qt::ItemIsDropEnabled | Qt::ItemIsEditable;

    return result | Qt::ItemNeverHasChildren;
}

FD3D::Transform *FDQUI::TransformModel::getTranfsorm()
{
    return m_transform;
}

const FD3D::Transform *FDQUI::TransformModel::getTranfsorm() const
{
    return m_transform;
}

void FDQUI::TransformModel::setTranfsorm(FD3D::Transform *transform)
{
    emit beginResetModel();
    m_transform = transform;
    emit endResetModel();
}
