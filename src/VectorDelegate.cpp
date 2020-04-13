#include <FDQUI/GUI/View/VectorDelegate.h>

#include <QDoubleSpinBox>

FDQUI::VectorDelegate::VectorDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{}

QWidget *FDQUI::VectorDelegate::createEditor(QWidget *parent,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    if(!index.isValid())
        return QStyledItemDelegate::createEditor(parent, option, index);

    if(!index.parent().isValid())
    {
        QDoubleSpinBox *sb = new QDoubleSpinBox(parent);
        sb->setRange(static_cast<double>(std::numeric_limits<float>::min()),
                     static_cast<double>(std::numeric_limits<float>::max()));
        sb->setValue(index.data(Qt::EditRole).toDouble());
        return sb;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void FDQUI::VectorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(!index.isValid())
    {
        QStyledItemDelegate::setEditorData(editor, index);
        return;
    }

    if(!index.parent().isValid())
    {
        QDoubleSpinBox *wid = static_cast<QDoubleSpinBox*>(editor);
        wid->setWhatsThis(index.data(Qt::WhatsThisRole).toString());
        wid->setToolTip(index.data(Qt::ToolTipRole).toString());
        wid->setStatusTip(index.data(Qt::StatusTipRole).toString());
        bool ok = false;
        double value = index.data(Qt::EditRole).toDouble(&ok);
        if(ok)
            wid->setValue(value);

        return;
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void FDQUI::VectorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    if(!index.parent().isValid())
    {
        QDoubleSpinBox *wid = static_cast<QDoubleSpinBox*>(editor);
        model->setData(index, wid->value());
    }
}
