#ifndef TRANSFORMMODEL_H
#define TRANSFORMMODEL_H

#include <QAbstractItemModel>
#include <FD3D/Utils/Transform.h>

class TransformModel : public QAbstractItemModel
{
    Q_OBJECT
    protected:
        /*
            mutable glm::mat4 m_mat;
            glm::vec3 m_position;
            glm::vec3 m_scale;
            glm::quat m_rotation;
            mutable bool m_isUpToDate;
        */

        enum class TransformFields: uint8_t
        {
            Position,
            Scale,
            Rotation,
            Matrice,
            IsUpToDate
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

        FD3D::Transform *getTranfsorm();
        const FD3D::Transform *getTranfsorm() const;

        void setTranfsorm(FD3D::Transform *transform);
        void unsetTranfsorm() { setTranfsorm(nullptr); }
};

#endif // TRANSFORMMODEL_H
