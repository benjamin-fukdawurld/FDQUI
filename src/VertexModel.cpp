#include <FDQUI/Model/VertexModel.h>

#include <FD3D/Mesh/AbstractMesh.h>

FDQUI::VertexModel::VertexModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_vertex(nullptr)
{

}

QModelIndex FDQUI::VertexModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!m_vertex)
        return QModelIndex();

    if(!parent.isValid())
    {
        return createIndex(row, column, static_cast<quintptr>(InternalId::Vertex));
    }

    quintptr id = parent.internalId();
    uint8_t type = id & 255; //get first byte

    switch(static_cast<InternalId>(type))
    {
        case InternalId::Uv:
        case InternalId::Color:
        {
            AgregatedId childId(id);

            if(childId.helper >= 2)
                return QModelIndex();

            if(childId.helper == 0)
            {
                childId.index = static_cast<uint8_t>(row);
                childId.helper = 1;
            }
            else
            {
                childId.component = static_cast<uint8_t>(row);
                childId.helper = 2;
            }

            return createIndex(row, column, childId);
        }

        default:
        {
            InternalId childId = getIdFromRow(row, static_cast<InternalId>(type));
            if(childId == InternalId::Invalid)
                return QModelIndex();

            return createIndex(row, column, static_cast<quintptr>(childId));
        }
    }
}

QModelIndex FDQUI::VertexModel::parent(const QModelIndex &index) const
{
    if(!m_vertex || !index.isValid())
        return QModelIndex();

    quintptr id = index.internalId();
    uint8_t type = id & 255; //get first byte

    switch(static_cast<InternalId>(type))
    {
        case InternalId::Vertex:
        return QModelIndex();

        case InternalId::Position:
        case InternalId::Normal:
        case InternalId::Tangent:
        case InternalId::Bitangent:
        return createIndex(0, 0, static_cast<quintptr>(InternalId::Vertex));


        case InternalId::PositionX:
        case InternalId::PositionY:
        case InternalId::PositionZ:
        return createIndex(getFieldRow(InternalId::Position), 0,
                           static_cast<quintptr>(InternalId::Position));

        case InternalId::NormalX:
        case InternalId::NormalY:
        case InternalId::NormalZ:
        return createIndex(getFieldRow(InternalId::Normal), 0,
                           static_cast<quintptr>(InternalId::Normal));

        case InternalId::TangentX:
        case InternalId::TangentY:
        case InternalId::TangentZ:
        return createIndex(getFieldRow(InternalId::Tangent), 0,
                           static_cast<quintptr>(InternalId::Tangent));

        case InternalId::BitangentX:
        case InternalId::BitangentY:
        case InternalId::BitangentZ:
        return createIndex(getFieldRow(InternalId::Bitangent), 0,
                           static_cast<quintptr>(InternalId::Bitangent));

        case InternalId::Uv:
        case InternalId::Color:
        {
            AgregatedId indexId(id);
            return createIndex(getFieldRow(indexId.id),
                               0, indexId.parent());
        }

        case InternalId::Invalid:
        return QModelIndex();
    }

    return QModelIndex();
}

int FDQUI::VertexModel::rowCount(const QModelIndex &parent) const
{
    if(!m_vertex)
        return 0;

    if(!parent.isValid())
        return 1;

    quintptr id = parent.internalId();
    uint8_t type = id & 255; //get first byte

    switch(static_cast<InternalId>(type))
    {
        case InternalId::Vertex:
        return 1
             + (m_vertex->getMesh()->hasVertexComponent(FD3D::VertexComponentType::Normal) ? 1 : 0)
             + (m_vertex->getMesh()->hasVertexComponent(FD3D::VertexComponentType::Tangent) ? 2 : 0)
             + (m_vertex->getMesh()->hasVertexComponent(FD3D::VertexComponentType::Texture) ? 1 : 0)
                * m_vertex->getMesh()->getNumberOfUvChannel()
             + (m_vertex->getMesh()->hasVertexComponent(FD3D::VertexComponentType::Color) ? 1 : 0)
                * m_vertex->getMesh()->getNumberOfColorChannel();

        case InternalId::Position:
        case InternalId::Normal:
        case InternalId::Tangent:
        case InternalId::Bitangent:
        return 3;

        case InternalId::PositionX:
        case InternalId::PositionY:
        case InternalId::PositionZ:
        case InternalId::NormalX:
        case InternalId::NormalY:
        case InternalId::NormalZ:
        case InternalId::TangentX:
        case InternalId::TangentY:
        case InternalId::TangentZ:
        case InternalId::BitangentX:
        case InternalId::BitangentY:
        case InternalId::BitangentZ:
        return 0;

        case InternalId::Uv:
        {
            AgregatedId parentId(id);
            if(parentId.helper == 2 || parentId.index >= m_vertex->getMesh()->getNumberOfUvChannel())
                return 0;

            if(parentId.helper == 1)
            return 2;

            return m_vertex->getMesh()->getNumberOfUvChannel();
        }

        case InternalId::Color:
        {
            AgregatedId parentId(id);
            if(parentId.helper == 2 || parentId.index >= m_vertex->getMesh()->getNumberOfUvChannel())
                return 0;

            if(parentId.helper == 1)
            return 4;

            return m_vertex->getMesh()->getNumberOfColorChannel();
        }

        case InternalId::Invalid:
        return 0;
    }

    return 0;
}

int FDQUI::VertexModel::columnCount(const QModelIndex &) const
{
    if(!m_vertex)
        return 0;

    return 1;
}

bool FDQUI::VertexModel::hasChildren(const QModelIndex &parent) const
{
    quintptr id = parent.internalId();
    uint8_t type = id & 255; //get first byte

    switch(static_cast<InternalId>(type))
    {
        case InternalId::Invalid:
        case InternalId::Vertex:
        case InternalId::Position:
        case InternalId::Normal:
        case InternalId::Tangent:
        case InternalId::Bitangent:
        return true;

        case InternalId::PositionX:
        case InternalId::PositionY:
        case InternalId::PositionZ:
        case InternalId::NormalX:
        case InternalId::NormalY:
        case InternalId::NormalZ:
        case InternalId::TangentX:
        case InternalId::TangentY:
        case InternalId::TangentZ:
        case InternalId::BitangentX:
        case InternalId::BitangentY:
        case InternalId::BitangentZ:
        return false;

        case InternalId::Uv:
        case InternalId::Color:
        {
            uint8_t helper = static_cast<uint8_t>((id & (255u << 24)) >> 24);

            if(helper == 2)
                return false;

            return true;
        }
    }

    return false;
}

QVariant FDQUI::VertexModel::data(const QModelIndex &index, int role) const
{
    if(!m_vertex || !index.isValid())
        return QVariant();

    quintptr id = index.internalId();
    uint8_t type = id & 255; //get first byte

    switch(static_cast<InternalId>(type))
    {
        case InternalId::Vertex:
        {
            if(role == Qt::DisplayRole)
                return tr("Vertex");
        }
        break;

        case InternalId::Position:
        {
            if(role == Qt::DisplayRole)
                return tr("Position");
        }
        break;

        case InternalId::Normal:
        {
            if(role == Qt::DisplayRole)
                return tr("Normal");
        }
        break;

        case InternalId::Tangent:
        {
            if(role == Qt::DisplayRole)
                return tr("Tangent");
        }
        break;

        case InternalId::Bitangent:
        {
            if(role == Qt::DisplayRole)
                return tr("Bitangent");
        }
        break;

        case InternalId::PositionX:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getPosition()->x;
        }
        break;

        case InternalId::PositionY:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getPosition()->y;
        }
        break;

        case InternalId::PositionZ:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getPosition()->z;
        }
        break;

        case InternalId::NormalX:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getNormal()->x;
        }
        break;

        case InternalId::NormalY:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getNormal()->y;
        }
        break;

        case InternalId::NormalZ:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getNormal()->z;
        }
        break;

        case InternalId::TangentX:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getTangent()->x;
        }
        break;

        case InternalId::TangentY:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getTangent()->y;
        }
        break;

        case InternalId::TangentZ:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getTangent()->z;
        }
        break;

        case InternalId::BitangentX:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getBitangent()->x;
        }
        break;

        case InternalId::BitangentY:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getBitangent()->y;
        }
        break;

        case InternalId::BitangentZ:
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_vertex->getBitangent()->z;
        }
        break;

        case InternalId::Uv:
        {
            AgregatedId dataId(id);
            if(dataId.helper == 0 && role == Qt::DisplayRole)
                return tr("Texture");

            if(dataId.helper == 1 && role == Qt::DisplayRole)
                return static_cast<int>(dataId.index);

            if(dataId.helper == 2 && (role == Qt::DisplayRole || role == Qt::EditRole))
            {
                if(dataId.component == 0)
                    return m_vertex->getUv(dataId.index)->x;

                if(dataId.component == 1)
                    return m_vertex->getUv(dataId.index)->y;
            }
        }
        break;

        case InternalId::Color:
        {
            AgregatedId dataId(id);
            if(dataId.helper == 0 && role == Qt::DisplayRole)
                return tr("Color");

            if(dataId.helper == 1 && role == Qt::DisplayRole)
                return static_cast<int>(dataId.index);

            if(dataId.helper == 2 && (role == Qt::DisplayRole || role == Qt::EditRole))
            {
                if(dataId.component == 0)
                    return m_vertex->getColor(dataId.index)->r;

                if(dataId.component == 1)
                    return m_vertex->getColor(dataId.index)->g;

                if(dataId.component == 2)
                    return m_vertex->getColor(dataId.index)->b;

                if(dataId.component == 3)
                    return m_vertex->getColor(dataId.index)->a;
            }

            return m_vertex->getMesh()->getNumberOfColorChannel();
        }

        case InternalId::Invalid:
        return QVariant();
    }

    return QVariant();
}

bool FDQUI::VertexModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!m_vertex || !index.isValid())
        return false;

    quintptr id = index.internalId();
    uint8_t type = id & 255; //get first byte

    switch(static_cast<InternalId>(type))
    {
        case InternalId::Invalid:
        case InternalId::Vertex:
        case InternalId::Position:
        case InternalId::Normal:
        case InternalId::Tangent:
        case InternalId::Bitangent:
        return false;

        case InternalId::PositionX:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getPosition()->x = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::PositionY:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getPosition()->y = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::PositionZ:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getPosition()->z = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::NormalX:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getNormal()->x = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::NormalY:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getNormal()->y = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::NormalZ:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getNormal()->z = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::TangentX:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getTangent()->x = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::TangentY:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getTangent()->y = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::TangentZ:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getTangent()->z = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::BitangentX:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getBitangent()->x = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::BitangentY:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getBitangent()->y = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::BitangentZ:
        {
            bool ok = false;
            float f = value.toFloat(&ok);
            if(!ok || (role != Qt::DisplayRole && role != Qt::EditRole))
                return false;

            m_vertex->getBitangent()->z = f;
            emit dataChanged(index, index);
            return true;
        }

        case InternalId::Uv:
        {
            AgregatedId dataId(id);
            if(dataId.helper == 2 && (role == Qt::DisplayRole || role == Qt::EditRole))
            {
                bool ok = false;
                float f = value.toFloat(&ok);
                if(!ok)
                    return false;

                if(dataId.component == 0)
                    m_vertex->getUv(dataId.index)->x = f;
                else if(dataId.component == 1)
                    m_vertex->getUv(dataId.index)->y = f;

                emit dataChanged(index, index);
                return true;
            }

            return false;
        }

        case InternalId::Color:
        {
            AgregatedId dataId(id);
            if(dataId.helper == 2 && (role == Qt::DisplayRole || role == Qt::EditRole))
            {
                bool ok = false;
                float f = value.toFloat(&ok);
                if(!ok)
                    return false;

                if(dataId.component == 0)
                    m_vertex->getColor(dataId.index)->r = f;
                else if(dataId.component == 1)
                    m_vertex->getColor(dataId.index)->g = f;
                else if(dataId.component == 2)
                    m_vertex->getColor(dataId.index)->b = f;
                else if(dataId.component == 3)
                    m_vertex->getColor(dataId.index)->a = f;

                emit dataChanged(index, index);
                return true;
            }

            return false;
        }
    }

    return false;
}

Qt::ItemFlags FDQUI::VertexModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result =
            Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled;

    if(index.internalId() == static_cast<quintptr>(InternalId::Vertex)
       || index.internalId() == static_cast<quintptr>(InternalId::Position)
       || index.internalId() == static_cast<quintptr>(InternalId::Normal)
       || index.internalId() == static_cast<quintptr>(InternalId::Tangent)
       || index.internalId() == static_cast<quintptr>(InternalId::Bitangent)
       || index.internalId() == static_cast<quintptr>(InternalId::Uv)
       || index.internalId() == static_cast<quintptr>(InternalId::Color))
        return result;

    AgregatedId dataId(index.internalId());
    if((dataId.id != InternalId::Uv && dataId.id != InternalId::Color))
        return result | Qt::ItemNeverHasChildren;
    else if(dataId.helper < 2)
        return result;

    return result |= Qt::ItemIsDropEnabled
                     | Qt::ItemIsEditable
                     | Qt::ItemNeverHasChildren;
}

const FD3D::VertexProxy *FDQUI::VertexModel::getVertex() const
{
    return m_vertex;
}

FD3D::VertexProxy *FDQUI::VertexModel::getVertex()
{
    return m_vertex;
}

void FDQUI::VertexModel::setVertex(FD3D::VertexProxy *vertex)
{
    emit beginResetModel();
    m_vertex = vertex;
    emit endResetModel();
}

int FDQUI::VertexModel::getFieldRow(FDQUI::VertexModel::InternalId field) const
{
    if(!m_vertex)
        return -1;

    const FD3D::AbstractMesh *mesh = m_vertex->getMesh();
    FD3D::VertexComponentType comp = internalIdToVertexComponent(field);
    if(comp == FD3D::VertexComponentType::Invalid || !mesh->hasVertexComponent(comp))
        return -1;


    switch(comp)
    {
        case FD3D::VertexComponentType::Position:
        return 0;

        case FD3D::VertexComponentType::Normal:
        return 1;

        case FD3D::VertexComponentType::Tangent:
        return (mesh->hasVertexComponent(FD3D::VertexComponentType::Normal) ? 2 : 1)
                + (field == InternalId::Bitangent ? 1 : 0);

        case FD3D::VertexComponentType::Texture:
        return ((mesh->hasVertexComponent(FD3D::VertexComponentType::Normal) ? 2 : 1)
                + (mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent) ? 2 : 0));

        case FD3D::VertexComponentType::Color:
        return ((mesh->hasVertexComponent(FD3D::VertexComponentType::Normal) ? 2 : 1)
                + (mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent) ? 2 : 0)
                + (mesh->hasVertexComponent(FD3D::VertexComponentType::Texture) ? 1 : 0));

        default:
        return -1;
    }
}

FDQUI::VertexModel::InternalId FDQUI::VertexModel::getIdFromRow(int row, FDQUI::VertexModel::InternalId id) const
{
    switch(id)
    {
        case InternalId::Invalid:
        return (row == 0 ? InternalId::Vertex : InternalId::Invalid);

        case InternalId::Vertex:
        {
            const FD3D::AbstractMesh *mesh = m_vertex->getMesh();
            switch(row)
            {
                case 0:
                return InternalId::Position;

                case 1:
                {
                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Normal))
                        return InternalId::Normal;

                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent))
                        return InternalId::Tangent;

                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Texture))
                        return InternalId::Uv;

                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Color))
                        return InternalId::Uv;

                    return InternalId::Invalid;
                }

                case 2:
                {
                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Normal))
                    {
                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent))
                            return InternalId::Tangent;

                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Texture))
                            return InternalId::Uv;

                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Color))
                            return InternalId::Color;

                        return InternalId::Invalid;
                    }

                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent))
                        return InternalId::Bitangent;

                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Texture))
                    {
                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Color))
                            return InternalId::Color;
                    }


                    return InternalId::Invalid;
                }

                case 3:
                {
                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Normal))
                    {
                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent))
                            return InternalId::Bitangent;

                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Texture))
                        {
                            if(mesh->hasVertexComponent(FD3D::VertexComponentType::Color))
                                return InternalId::Color;
                        }

                        return InternalId::Invalid;
                    }

                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent))
                    {
                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Texture))
                            return InternalId::Uv;

                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Color))
                            return InternalId::Color;
                    }

                    return InternalId::Invalid;
                }

                case 4:
                {
                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Normal))
                    {
                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent))
                        {
                            if(mesh->hasVertexComponent(FD3D::VertexComponentType::Texture))
                                return InternalId::Uv;

                            if(mesh->hasVertexComponent(FD3D::VertexComponentType::Color))
                                return InternalId::Color;
                        }

                        return InternalId::Invalid;
                    }

                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent))
                    {
                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Texture))
                        {
                            if(mesh->hasVertexComponent(FD3D::VertexComponentType::Color))
                                return InternalId::Color;
                        }
                    }

                    return InternalId::Invalid;
                }

                case 5:
                {
                    if(mesh->hasVertexComponent(FD3D::VertexComponentType::Normal))
                    {
                        if(mesh->hasVertexComponent(FD3D::VertexComponentType::Tangent))
                        {
                            if(mesh->hasVertexComponent(FD3D::VertexComponentType::Texture))
                            {
                                if(mesh->hasVertexComponent(FD3D::VertexComponentType::Color))
                                    return InternalId::Color;
                            }
                        }
                    }

                    return InternalId::Invalid;
                }
            }
            return InternalId::Invalid;
        }

        case InternalId::Position:
        {
            switch(row)
            {
                case 0:
                return InternalId::PositionX;

                case 1:
                return InternalId::PositionY;

                case 2:
                return InternalId::PositionZ;

                default:
                return InternalId::Invalid;
            }
        }

        case InternalId::Normal:
        {
            switch(row)
            {
                case 0:
                return InternalId::NormalX;

                case 1:
                return InternalId::NormalY;

                case 2:
                return InternalId::NormalZ;

                default:
                return InternalId::Invalid;
            }
        }

        case InternalId::Tangent:
        {
            switch(row)
            {
                case 0:
                return InternalId::TangentX;

                case 1:
                return InternalId::TangentY;

                case 2:
                return InternalId::TangentZ;

                default:
                return InternalId::Invalid;
            }
        }

        case InternalId::Bitangent:
        {
            switch(row)
            {
                case 0:
                return InternalId::BitangentX;

                case 1:
                return InternalId::BitangentY;

                case 2:
                return InternalId::BitangentZ;

                default:
                return InternalId::Invalid;
            }
        }

        default:
        return InternalId::Invalid;
    }
}

FD3D::VertexComponentType FDQUI::VertexModel::internalIdToVertexComponent(FDQUI::VertexModel::InternalId field)
{
    switch(field)
    {
        case InternalId::Position:
        return FD3D::VertexComponentType::Position;

        case InternalId::Normal:
        return FD3D::VertexComponentType::Normal;

        case InternalId::Tangent:
        case InternalId::Bitangent:
        return FD3D::VertexComponentType::Tangent;

        case InternalId::Uv:
        return FD3D::VertexComponentType::Texture;

        case InternalId::Color:
        return FD3D::VertexComponentType::Color;

        case InternalId::Invalid:
        case InternalId::Vertex:
        case InternalId::PositionX:
        case InternalId::PositionY:
        case InternalId::PositionZ:
        case InternalId::NormalX:
        case InternalId::NormalY:
        case InternalId::NormalZ:
        case InternalId::TangentX:
        case InternalId::TangentY:
        case InternalId::TangentZ:
        case InternalId::BitangentX:
        case InternalId::BitangentY:
        case InternalId::BitangentZ:
        return FD3D::VertexComponentType::Invalid;
    }

    return FD3D::VertexComponentType::Invalid;
}
