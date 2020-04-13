#ifndef QUATERNIONMODEL_H
#define QUATERNIONMODEL_H

#include <FDQUI/Model/MatriceModel.h>
#include <QAbstractProxyModel>

namespace FDQUI
{
    class QuaternionModel: public MatriceModel
    {
        Q_OBJECT
        public:
            using MatriceModel::MatriceModel;

            ~QuaternionModel() override = default;

            glm::quat &getQuaternion();

            const glm::quat &getQuaternion() const;

            void setQuaternion(glm::quat &q);

            void unsetQuaternion();

        private:
            using MatriceModel::setValues;
            using MatriceModel::unsetValues;
    };

    class RowQuaternionProxyModel: public QAbstractProxyModel
    {
        Q_OBJECT
        public:
            RowQuaternionProxyModel(QObject *parent = nullptr) :
                QAbstractProxyModel(parent)
            {}

            ~RowQuaternionProxyModel() override = default;

            QModelIndex	index(int row,
                              int column,
                              const QModelIndex &parent = QModelIndex()
                ) const override;

            QModelIndex parent(const QModelIndex &index) const override;

            int rowCount(const QModelIndex &parent = QModelIndex()) const override;

            int columnCount(const QModelIndex &parent = QModelIndex()) const override;

            QVariant headerData(
                    int section,
                    Qt::Orientation orientation,
                    int role = Qt::DisplayRole
                ) const override;

            QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;

            QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
    };
}

#endif // QUATERNIONMODEL_H
