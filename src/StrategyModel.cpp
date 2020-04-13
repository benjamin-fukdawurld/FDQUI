#include <FDQUI/Model/StrategyModel.h>

FDQUI::StrategyModel::StrategyModel(QObject *parent) : QAbstractItemModel(parent)
{}

QModelIndex FDQUI::StrategyModel::index(int row, int column, const QModelIndex &parent) const
{
    if(m_indexStrategy)
        return m_indexStrategy(*this, row, column, parent);

    return QModelIndex();
}

QModelIndex FDQUI::StrategyModel::parent(const QModelIndex &index) const
{
    if(m_parentStrategy)
        return m_parentStrategy(*this, index);

    return QModelIndex();
}

int FDQUI::StrategyModel::rowCount(const QModelIndex &parent) const
{
    if(m_rowCountStrategy)
        return m_rowCountStrategy(*this, parent);

    return 0;
}

int FDQUI::StrategyModel::columnCount(const QModelIndex &parent) const
{
    if(m_columnCountStrategy)
        return m_columnCountStrategy(*this, parent);

    return 0;
}

bool FDQUI::StrategyModel::hasChildren(const QModelIndex &parent) const
{
    if(m_hasChildrenStrategy)
        return m_hasChildrenStrategy(*this, parent);

    return flags(parent) & Qt::ItemNeverHasChildren;
}

QVariant FDQUI::StrategyModel::data(const QModelIndex &index, int role) const
{
    if(m_dataStrategy)
        return m_dataStrategy(*this, index, role);

    return QVariant();
}

QVariant FDQUI::StrategyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(m_headerDataStrategy)
        return m_headerDataStrategy(*this, section, orientation, role);

    return QVariant();
}

bool FDQUI::StrategyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(m_setDataStrategy)
        return m_setDataStrategy(*this, index, value, role);

    return false;
}

Qt::ItemFlags FDQUI::StrategyModel::flags(const QModelIndex &index) const
{
    if(m_flagsStrategy)
        return m_flagsStrategy(*this, index);

    return QAbstractItemModel::flags(index);
}

QVariant FDQUI::AbstractModelDataGetter::operator()(
        const QAbstractItemModel &model,
        const QModelIndex &index,
        int role
    )
{
    DataGetter dg = this->operator[](role);
    if(dg)
        return dg(model, index);

    return QVariant();
}

bool FDQUI::AbstractModelDataSetter::operator()(
        const QAbstractItemModel &model,
        const QModelIndex &index,
        const QVariant &value,
        int role
    )
{
    DataSetter ds = this->operator[](role);
    if(ds)
        return ds(model, index, value);

    return false;
}

QVariant FDQUI::AbstractModelHeaderDataGetter::operator()(
        const QAbstractItemModel &model,
        int section,
        Qt::Orientation orientation,
        int role
    )
{
    HeaderDataGetter hdg = this->operator[](role);
    if(hdg)
        return hdg(model, section, orientation);

    return QVariant();
}
