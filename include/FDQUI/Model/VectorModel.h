#ifndef VECTORMODEL_H
#define VECTORMODEL_H

#include <FDQUI/Model/MatriceModel.h>
#include <QAbstractProxyModel>

namespace FDQUI
{

    class VectorModel: public MatriceModel
    {
        Q_OBJECT
        public:
            using MatriceModel::MatriceModel;

            ~VectorModel() override = default;

            template<int S>
            glm::vec<S, float, glm::defaultp> &getVector()
            {
                return *reinterpret_cast<glm::vec<S, float, glm::defaultp>*>(getValues());
            }

            template<int S>
            const glm::vec<S, float, glm::defaultp> &getVector() const
            {
                return *reinterpret_cast<const glm::vec<S, float, glm::defaultp>*>(getValues());
            }

            template<int S>
            void setVector(glm::vec<S, float, glm::defaultp> &v)
            {
                setValues(glm::value_ptr(v), S, 1);
            }

            void unsetVector();
        private:
            using MatriceModel::setValues;
            using MatriceModel::unsetValues;
    };

    class RowVectorProxyModel: public QAbstractProxyModel
    {
        Q_OBJECT
        public:
            RowVectorProxyModel(QObject *parent = nullptr) :
                QAbstractProxyModel(parent)
            {}

            ~RowVectorProxyModel() override = default;

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

#endif // VECTORMODEL_H
