#ifndef TRANSFORMMODEL_H
#define TRANSFORMMODEL_H

#include <QAbstractItemModel>
#include <FD3D/Utils/Transform.h>

namespace FDQUI
{
    class TransformModel : public QAbstractItemModel
    {
        Q_OBJECT
        public:
            enum class TransformField: uint8_t
            {
                Position,
                Scale,
                Rotation,
                Matrix,
                IsUpToDate
            };

            enum class InternalId: uint8_t
            {
                Transform,
                Position,
                PositionX,
                PositionY,
                PositionZ,
                Scale,
                ScaleX,
                ScaleY,
                ScaleZ,
                Rotation,
                RotationW,
                RotationX,
                RotationY,
                RotationZ,
                Matrix,
                IsUpToDate = Matrix + 16 + 1
            };

            static constexpr size_t NumberOfFields = 5;

        protected:
            FD3D::Transform *m_transform;

        public:
            TransformModel(QObject *parent = nullptr);

            ~TransformModel() override = default;

            QModelIndex	index(int row,
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

            FD3D::Transform *getTranfsorm();
            const FD3D::Transform *getTranfsorm() const;

            void setTranfsorm(FD3D::Transform *transform);
            void unsetTranfsorm() { setTranfsorm(nullptr); }
    };
}

#endif // TRANSFORMMODEL_H
