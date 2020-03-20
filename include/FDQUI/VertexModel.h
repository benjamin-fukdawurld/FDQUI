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

        protected:
            FD3D::VertexProxy *m_vertex;


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

            QVariant headerData(
                    int section,
                    Qt::Orientation orientation,
                    int role = Qt::DisplayRole
                ) const override;

            bool setData(
                    const QModelIndex &index,
                    const QVariant &value,
                    int role = Qt::EditRole
                ) override;

            Qt::ItemFlags flags(const QModelIndex &index) const override;
    };

}

#endif // VERTEXMODEL_H
