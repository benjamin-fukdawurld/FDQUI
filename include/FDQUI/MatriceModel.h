#ifndef VECTORMODEL_H
#define VECTORMODEL_H

#include <QAbstractItemModel>
#include <QLayout>

#include <unordered_map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace FDQUI
{
    class MatriceModel;

    QVariant defaultHeaderData(const MatriceModel &model,
                               int section,
                               Qt::Orientation orientation,
                               int role);

    QVariant defaultData(const MatriceModel &model,
                         size_t row,
                         size_t column);

    class MatriceModel : public QAbstractItemModel
    {
        public:
            typedef std::function<
                QVariant(
                    const MatriceModel &,
                    int,
                    Qt::Orientation,
                    int
                )> HeaderDataStrategy;

            typedef std::function<
                QVariant(
                    const MatriceModel &,
                    size_t,
                    size_t
                )> DataStrategy;

            typedef std::unordered_map<int, DataStrategy> DataStrategyMap;

        protected:
            HeaderDataStrategy m_headerDataStrategy;
            DataStrategyMap m_dataStrategies;
            float *m_values;
            size_t m_nbRow;
            size_t m_nbCol;


        public:
            MatriceModel(
                    HeaderDataStrategy headerDatastrategy = &defaultHeaderData,
                    const DataStrategyMap &dataStrategies = {{ Qt::DisplayRole, &defaultData }},
                    QObject *parent = nullptr
                );
            ~MatriceModel() override = default;

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

            float *getValues() { return m_values; }
            const float *getValues() const { return m_values; }

            void setValues(float *data, size_t nbRow, size_t nbCol);

            template<int S>
            void setValues(glm::vec<S, float, glm::defaultp> &v)
            {
                setValues(glm::value_ptr(v), S, 1);
            }

            void setValues(glm::quat &q)
            {
                setValues(glm::value_ptr(q), 4, 1);
            }

            template<int C, int R>
            void setValues(glm::mat<C, R, float, glm::defaultp> &mat)
            {
                setValues(glm::value_ptr(mat), R, C);
            }

            void unsetValues() { setValues(nullptr, 0, 0); }
    };

    class VectorModel: public MatriceModel
    {
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

            void unsetVector() { setValues(nullptr, 0, 0); }

        private:
            using MatriceModel::getValues;
            using MatriceModel::setValues;
            using MatriceModel::unsetValues;
    };

    class QuaternionModel: public MatriceModel
    {
        public:
            using MatriceModel::MatriceModel;

            ~QuaternionModel() override = default;

            glm::quat &getQuaternion()
            {
                return *reinterpret_cast<glm::quat*>(getValues());
            }

            const glm::quat &getQuaternion() const
            {
                return *reinterpret_cast<const glm::quat*>(getValues());
            }

            void setQuaternion(glm::quat &q)
            {
                setValues(glm::value_ptr(q), 4, 1);
            }

            void unsetQuaternion() { setValues(nullptr, 0, 0); }

        private:
            using MatriceModel::getValues;
            using MatriceModel::setValues;
            using MatriceModel::unsetValues;
    };
}

#endif // VECTORMODEL_H
