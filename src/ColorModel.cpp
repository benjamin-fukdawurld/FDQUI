#include "include/FDQUI/Model/ColorModel.h"

#include <QColor>

ColorModel::ColorModel(QObject *parent):
    QAbstractItemModel(parent),
    m_color(nullptr)
{}

const glm::vec4 *ColorModel::getColor() const
{
    return m_color;
}

glm::vec4 *ColorModel::getColor()
{
    return m_color;
}

QModelIndex ColorModel::index(int row, int column, const QModelIndex &parent) const
{
    if(m_color == nullptr || column != 0)
        return QModelIndex();

    if(!parent.isValid())
    {
        if(row != 0 || column != 0)
            return QModelIndex();

        return createIndex(row, column, static_cast<quintptr>(InternalId::Color));
    }

    if(static_cast<InternalId>(parent.internalId()) == InternalId::Color)
    {
        switch(row)
        {
            case 0:
            return createIndex(0, 0, static_cast<quintptr>(InternalId::Red));

            case 1:
            return createIndex(0, 0, static_cast<quintptr>(InternalId::Green));

            case 2:
            return createIndex(0, 0, static_cast<quintptr>(InternalId::Blue));

            case 3:
            return createIndex(0, 0, static_cast<quintptr>(InternalId::Alpha));
        }
    }

    return QModelIndex();
}

QModelIndex ColorModel::parent(const QModelIndex &index) const
{
    if(!index.isValid()
       || static_cast<InternalId>(index.internalId()) == InternalId::Color)
        return QModelIndex();

    return createIndex(0, 0, static_cast<quintptr>(InternalId::Color));
}

int ColorModel::rowCount(const QModelIndex &parent) const
{
    if(m_color == nullptr)
        return 0;

    if(!parent.isValid())
        return 1;


    if(static_cast<InternalId>(parent.internalId()) == InternalId::Color)
        return 4;

    return 0;
}

int ColorModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

bool ColorModel::hasChildren(const QModelIndex &parent) const
{
    if(m_color == nullptr)
        return false;

    return !parent.isValid() || static_cast<InternalId>(parent.internalId()) == InternalId::Color;
}

QVariant ColorModel::data(const QModelIndex &index, int role) const
{
    if(m_color == nullptr || !index.isValid() || index.column() != 0)
        return QVariant();

    switch(static_cast<InternalId>(index.internalId()))
    {
        case InternalId::Color:
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return tr("Color");

            if(role == Qt::DecorationRole)
            {
                glm::ivec4 v = *m_color * 255.0f;
                return QColor(v.r, v.g, v.b, v.a);
            }
        break;

        case InternalId::Red:
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_color->r;
        break;

        case InternalId::Green:
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_color->g;
        break;

        case InternalId::Blue:
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_color->b;
        break;

        case InternalId::Alpha:
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_color->a;
        break;
    }

    return QModelIndex();
}

bool ColorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

Qt::ItemFlags ColorModel::flags(const QModelIndex &index) const
{

}

void ColorModel::setColor(glm::vec4 *color)
{
    emit beginResetModel();
    m_color = color;
    emit endResetModel();
}

void ColorModel::unsetColor()
{
    setColor(nullptr);
}
