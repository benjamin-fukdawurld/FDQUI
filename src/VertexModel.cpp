#include "include/FDQUI/VertexModel.h"

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
        case InternalId::Vertex:
            switch(row)
            {
                case 0:
                return createIndex(row, column, static_cast<quintptr>(InternalId::Position));

                case 1:
                return createIndex(row, column, static_cast<quintptr>(InternalId::Normal));

                case 2:
                return createIndex(row, column, static_cast<quintptr>(InternalId::Tangent));

                case 3:
                return createIndex(row, column, static_cast<quintptr>(InternalId::Bitangent));

                case 4:
                return createIndex(row, column, static_cast<quintptr>(InternalId::Uv));

                case 5:
                return createIndex(row, column, static_cast<quintptr>(InternalId::Color));

                default:
                return QModelIndex();
            }

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

        case InternalId::Normal:
            if(column != 0)
                return QModelIndex();

            switch(row)
            {
                case 0:
                return createIndex(row, column, static_cast<quintptr>(InternalId::NormalX));

                case 1:
                return createIndex(row, column, static_cast<quintptr>(InternalId::NormalY));

                case 2:
                return createIndex(row, column, static_cast<quintptr>(InternalId::NormalZ));

                default:
                return QModelIndex();
            }

        case InternalId::Tangent:
            if(column != 0)
                return QModelIndex();

            switch(row)
            {
                case 0:
                return createIndex(row, column, static_cast<quintptr>(InternalId::TangentX));

                case 1:
                return createIndex(row, column, static_cast<quintptr>(InternalId::TangentY));

                case 2:
                return createIndex(row, column, static_cast<quintptr>(InternalId::TangentZ));

                default:
                return QModelIndex();
            }

        case InternalId::Bitangent:
            if(column != 0)
                return QModelIndex();

            switch(row)
            {
                case 0:
                return createIndex(row, column, static_cast<quintptr>(InternalId::BitangentX));

                case 1:
                return createIndex(row, column, static_cast<quintptr>(InternalId::BitangentY));

                case 2:
                return createIndex(row, column, static_cast<quintptr>(InternalId::BitangentZ));

                default:
                return QModelIndex();
            }

        case InternalId::Uv:
        case InternalId::Color:
        {
            uint8_t index = static_cast<uint8_t>((id & (255 << 8)) >> 8);
            uint8_t component = static_cast<uint8_t>((id & (255 << 16)) >> 16);
            uint8_t helper = (index != 0 ? (component != 0 ? 2 : 1) : 0);
            if(component != 0)
                return QModelIndex();

            quintptr resultId = static_cast<quintptr>(type);
            resultId |= static_cast<quintptr>(index) << 8;
            resultId |= static_cast<quintptr>(component) << 16;
            resultId |= static_cast<quintptr>(helper) << 24;

            return createIndex(row, column, resultId);
        }

        default:
        return QModelIndex();
    }

    return QModelIndex();
}

QModelIndex FDQUI::VertexModel::parent(const QModelIndex &index) const
{
    if(!m_vertex)
        return QModelIndex();

    if(!index.isValid())
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
        return createIndex(0, 0, static_cast<quintptr>(InternalId::Position));

        case InternalId::NormalX:
        case InternalId::NormalY:
        case InternalId::NormalZ:
        return createIndex(1, 0, static_cast<quintptr>(InternalId::Normal));

        case InternalId::TangentX:
        case InternalId::TangentY:
        case InternalId::TangentZ:
        return createIndex(2, 0, static_cast<quintptr>(InternalId::Tangent));

        case InternalId::BitangentX:
        case InternalId::BitangentY:
        case InternalId::BitangentZ:
        return createIndex(3, 0, static_cast<quintptr>(InternalId::Bitangent));

        case InternalId::Uv:
        case InternalId::Color:
        {
            uint8_t index = static_cast<uint8_t>((id & (255 << 8)) >> 8);
            uint8_t component = static_cast<uint8_t>((id & (255 << 16)) >> 16);
            uint8_t helper = (index != 0 ? (component != 0 ? 2 : 1) : 0);
            if(helper == 0)
                return createIndex(0, 0, static_cast<quintptr>(InternalId::Vertex));

            if(helper == 1)
            {
                return createIndex(static_cast<InternalId>(type) == InternalId::Uv ? 4 : 5,
                                   0, static_cast<quintptr>(type));
            }

            quintptr resultId = static_cast<quintptr>(type);
            resultId |= static_cast<quintptr>(index) << 8;
            resultId |= static_cast<quintptr>(1) << 24;

            return createIndex(index, 0, static_cast<quintptr>(type));

        }
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
            uint8_t index = static_cast<uint8_t>((id & (255 << 8)) >> 8);
            uint8_t component = static_cast<uint8_t>((id & (255 << 16)) >> 16);
            uint8_t helper = (index != 0 ? (component != 0 ? 2 : 1) : 0);

            if(helper == 2 || index >= m_vertex->getMesh()->getNumberOfUvChannel())
                return 0;

            if(helper == 1)
            return 2;

            return m_vertex->getMesh()->getNumberOfUvChannel();
        }

        case InternalId::Color:
        {
            uint8_t index = static_cast<uint8_t>((id & (255 << 8)) >> 8);
            uint8_t component = static_cast<uint8_t>((id & (255 << 16)) >> 16);
            uint8_t helper = (index != 0 ? (component != 0 ? 2 : 1) : 0);

            if(helper == 2 || index >= m_vertex->getMesh()->getNumberOfColorChannel())
                return 0;

            if(helper == 1)
            return 2;

            return m_vertex->getMesh()->getNumberOfColorChannel();
        }
    }

    return 0;
}
