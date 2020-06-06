#ifndef VERTEXMODEL_H
#define VERTEXMODEL_H

#include <QAbstractItemModel>

#include <FD3D/Utils/VertexProxy.h>

namespace FDQUI
{

    class VertexModel : public QAbstractItemModel
    {
        Q_OBJECT
        public:
            enum class InternalId : uint8_t
            {
                Invalid,
                Vertex,
                Position,
                PositionX,
                PositionY,
                PositionZ,
                Normal,
                NormalX,
                NormalY,
                NormalZ,
                Tangent,
                TangentX,
                TangentY,
                TangentZ,
                Bitangent,
                BitangentX,
                BitangentY,
                BitangentZ,
                Uv,
                Color
            };

        private:
            struct AgregatedId
            {
                InternalId id;
                uint8_t index;
                uint8_t component;
                uint8_t helper;

                AgregatedId(InternalId id = InternalId::Invalid,
                            uint8_t index = 0,
                            uint8_t component = 0,
                            uint8_t helper = 0) :
                    id(id),
                    index(index),
                    component(component),
                    helper(helper)
                {}

                AgregatedId(quintptr qid):
                    id(static_cast<InternalId>(qid & 255)),
                    index((qid & (255u << 8) >> 8)),
                    component((qid & (255u << 16) >> 16)),
                    helper((qid & (255u << 24) >> 24))
                {}

                inline operator quintptr() const
                {
                    return static_cast<quintptr>(id)
                           | (static_cast<quintptr>(index) << 8)
                           | (static_cast<quintptr>(component) << 16u)
                           | (static_cast<quintptr>(helper) << 24u);
                }

                AgregatedId parent() const
                {
                    if(helper == 0)
                        return { InternalId::Vertex };

                    if(helper == 1)
                        return { id };

                    return { id, index };
                }
            };

        protected:
            FD3D::VertexProxy2 *m_vertex;


        public:
            VertexModel(QObject *parent = nullptr);

            QModelIndex	index(
                    int row,
                    int column,
                    const QModelIndex &parent = QModelIndex()
                ) const override;

            QModelIndex parent(const QModelIndex &index) const override;

            int rowCount(const QModelIndex &parent = QModelIndex()) const override;

            int columnCount(const QModelIndex &parent = QModelIndex()) const override;

            bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

            bool setData(
                    const QModelIndex &index,
                    const QVariant &value,
                    int role = Qt::EditRole
                ) override;

            Qt::ItemFlags flags(const QModelIndex &index) const override;

            const FD3D::VertexProxy2 *getVertex() const;

            FD3D::VertexProxy2 *getVertex();

            void setVertex(FD3D::VertexProxy2 *vertex);

            void unsetVertex() { setVertex(nullptr);}

        private:
            int getFieldRow(InternalId field) const;
            InternalId getIdFromRow(int row, InternalId id) const;

            static FD3D::VertexComponentType internalIdToVertexComponent(InternalId field);
    };

}

#endif // VERTEXMODEL_H
