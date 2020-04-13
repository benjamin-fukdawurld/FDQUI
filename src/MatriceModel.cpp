#include <FDQUI/Model/MatriceModel.h>

#include <string>

#include <QDebug>

FDQUI::MatriceModel::MatriceModel(
        HeaderDataStrategy headerDatastrategy,
        const DataStrategyMap &dataStrategies,
        QObject *parent
        ) :
    QAbstractItemModel(parent),
    m_headerDataStrategy(headerDatastrategy),
    m_dataStrategies(dataStrategies),
    m_values(nullptr),
    m_nbRow(0),
    m_nbCol(0)
{

}

QModelIndex FDQUI::MatriceModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

QModelIndex FDQUI::MatriceModel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid())
        return QModelIndex();

    return createIndex(row, column, m_values);
}

int FDQUI::MatriceModel::rowCount(const QModelIndex &) const
{
    return m_values != nullptr ? static_cast<int>(m_nbRow) : 0;
}

int FDQUI::MatriceModel::columnCount(const QModelIndex &) const
{
    return m_values != nullptr ? static_cast<int>(m_nbCol) : 0;
}

bool FDQUI::MatriceModel::hasChildren(const QModelIndex &parent) const
{
    if(parent.isValid())
        return false;

    return true;
}

QVariant FDQUI::MatriceModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()
       || index.row() < 0 || index.row() >= rowCount(index.parent())
       || index.column() < 0 || index.column() >= columnCount(index.parent()))
        return QVariant();

    auto it = m_dataStrategies.find(role);
    if(it != m_dataStrategies.end())
        return it->second(
                    *this,
                    static_cast<size_t>(index.row()),
                    static_cast<size_t>(index.column()));

    return QVariant();
}

QVariant FDQUI::MatriceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(m_headerDataStrategy)
        return m_headerDataStrategy(*this, section, orientation, role);

    return QVariant();
}

bool FDQUI::MatriceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    if(!index.isValid()
       || index.row() < 0 || index.row() >= rowCount(index.parent())
       || index.column() < 0 || index.column() >= columnCount(index.parent()))
        return false;

    if(!value.isValid())
        return false;

    bool ok = false;
    float f = value.toFloat(&ok);
    if(!ok)
        return false;

    int pos = index.row() + index.column() * static_cast<int>(m_nbRow);
    m_values[pos] = f;

    dataChanged(index, index);

    return true;
}

Qt::ItemFlags FDQUI::MatriceModel::flags(const QModelIndex &index) const
{
    if(!index.isValid()
       || index.row() < 0 || index.row() >= rowCount(index.parent())
       || index.column() < 0 || index.column() >= columnCount(index.parent()))
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled
            | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

void FDQUI::MatriceModel::setValues(float *data, size_t nbRow, size_t nbCol)
{
    emit beginResetModel();
    m_values = data;
    m_nbRow = nbRow;
    m_nbCol = nbCol;
    emit endResetModel();
}

QVariant FDQUI::MatriceModel::defaultHeaderData(const FDQUI::MatriceModel &model,
                                                int section,
                                                Qt::Orientation orientation,
                                                int role)
{
    if(role != Qt::DisplayRole || section < 0)
        return QVariant();

    if(orientation == Qt::Horizontal)
    {
        if(section >= model.columnCount())
            return QVariant();

        return section;
    }

    if(section >= model.rowCount())
        return QVariant();

    QString result;

    if(model.rowCount() < 4)
    {
        result += static_cast<char>('x' + section);
        return result;
    }

    int mod = section % 26;
    int div = section / 26;
    if(mod < 4)
        result += static_cast<char>('w' + mod);
    else
        result += static_cast<char>('a' + mod - 4);

    if(div != 0)
        result += QString::number(div);

    return result;
}

QVariant FDQUI::MatriceModel::defaultData(const FDQUI::MatriceModel &model, size_t row, size_t column)
{
    return model.getValues()[row + column * static_cast<size_t>(model.rowCount())];
}
