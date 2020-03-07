#ifndef STRATEGYMODEL_H
#define STRATEGYMODEL_H

#include <QAbstractItemModel>

namespace FDQUI
{
    class StrategyModel : public QAbstractItemModel
    {
            Q_OBJECT
        public:
            typedef std::function<
                QModelIndex(
                    const StrategyModel&,
                    int,
                    int,
                    const QModelIndex &)> IndexStrategy;

            typedef std::function<
                QModelIndex(
                    const StrategyModel&,
                    const QModelIndex &)> ParentStrategy;

            typedef std::function<
                int(const StrategyModel&, const QModelIndex &)> RowCountStrategy;
            typedef std::function<
                int(const StrategyModel&, const QModelIndex &)> ColumnCountStrategy;

            typedef std::function<
                bool(const StrategyModel&, const QModelIndex &)> HasChildrenStrategy;

            typedef std::function<
                QVariant(const StrategyModel&, const QModelIndex &, int)> DataStrategy;

            typedef std::function<
                QVariant(const StrategyModel&, int, Qt::Orientation, int)> HeaderDataStrategy;

            typedef std::function<bool(StrategyModel&,
                                       const QModelIndex &,
                                       const QVariant &,
                                       int role
                                       )> SetDataStrategy;

            typedef std::function<
            Qt::ItemFlags(const StrategyModel&, const QModelIndex &)> FlagsStrategy;

        protected:
            IndexStrategy m_indexStrategy;
            ParentStrategy m_parentStrategy;
            RowCountStrategy m_rowCountStrategy;
            ColumnCountStrategy m_columnCountStrategy;
            HasChildrenStrategy m_hasChildrenStrategy;
            DataStrategy m_dataStrategy;
            HeaderDataStrategy m_headerDataStrategy;
            SetDataStrategy m_setDataStrategy;
            FlagsStrategy m_flagsStrategy;

        public:
            explicit StrategyModel(QObject *parent = nullptr);

            template<
                    typename IndexStrategyType,
                    typename ParentStrategyType,
                    typename RowCountStrategyType,
                    typename ColumnCountStrategyType,
                    typename HasChildrenStrategyType,
                    typename DataStrategyType,
                    typename HeaderDataStrategyType,
                    typename SetDataStrategyType,
                    typename FlagsStrategyType
                >
            StrategyModel(
                    IndexStrategyType indexStrategy,
                    ParentStrategyType parentStrategy,
                    RowCountStrategyType rowCountStrategy,
                    ColumnCountStrategyType columnCountStrategy,
                    HasChildrenStrategyType hasChildrenStrategy,
                    DataStrategyType dataStrategy,
                    HeaderDataStrategyType headerDataStrategy,
                    SetDataStrategyType setDataStrategy,
                    FlagsStrategyType flagsStrategy,
                    QObject *parent = nullptr
                ) :
                QAbstractItemModel(parent),
                m_indexStrategy(indexStrategy),
                m_parentStrategy(parentStrategy),
                m_rowCountStrategy(rowCountStrategy),
                m_columnCountStrategy(columnCountStrategy),
                m_hasChildrenStrategy(hasChildrenStrategy),
                m_dataStrategy(dataStrategy),
                m_headerDataStrategy(headerDataStrategy),
                m_setDataStrategy(setDataStrategy),
                m_flagsStrategy(flagsStrategy)
            {}

            ~StrategyModel() override = default;

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

    class AbstractModelDataGetter
    {
        public:
            typedef std::function<
                QVariant(const QAbstractItemModel &, const QModelIndex &index)> DataGetter;

        public:
            AbstractModelDataGetter() = default;
            virtual ~AbstractModelDataGetter() = default;

            QVariant operator()(
                    const QAbstractItemModel &model,
                    const QModelIndex &index,
                    int role = Qt::DisplayRole
                );

            virtual DataGetter operator[](int role) = 0;
    };

    class AbstractModelDataSetter
    {
        public:
            typedef std::function<
                bool(const QAbstractItemModel &, const QModelIndex &, const QVariant&)> DataSetter;

        public:
            AbstractModelDataSetter() = default;
            virtual ~AbstractModelDataSetter() = default;

            bool operator()(
                    const QAbstractItemModel &model,
                    const QModelIndex &index,
                    const QVariant &value,
                    int role = Qt::DisplayRole
                );

            virtual DataSetter operator[](int role) = 0;
    };

    class AbstractModelHeaderDataGetter
    {
        public:
            typedef std::function<
                QVariant(const QAbstractItemModel &, int, Qt::Orientation)> HeaderDataGetter;

        public:
            AbstractModelHeaderDataGetter() = default;
            virtual ~AbstractModelHeaderDataGetter() = default;

            QVariant operator()(
                    const QAbstractItemModel &model,
                    int section,
                    Qt::Orientation orientation,
                    int role = Qt::DisplayRole
                );

            virtual HeaderDataGetter operator[](int role) = 0;
    };
}

#endif // STRATEGYMODEL_H
