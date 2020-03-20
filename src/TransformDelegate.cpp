#include "include/FDQUI/TransformDelegate.h"

#include <FDQUI/TransformModel.h>

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QLabel>

#include <limits>

FDQUI::TransformDelegate::TransformDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

QWidget *FDQUI::TransformDelegate::createEditor(QWidget *parent,
                                                const QStyleOptionViewItem &option,
                                                const QModelIndex &index) const
{
    if(!index.isValid())
        return QStyledItemDelegate::createEditor(parent, option, index);

    if(index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionZ)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleZ)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationW)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationZ))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setRange(static_cast<double>(std::numeric_limits<float>::min()),
                         static_cast<double>(std::numeric_limits<float>::max()));
        editor->setValue(index.data(Qt::EditRole).toDouble());
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void FDQUI::TransformDelegate::setEditorData(QWidget *editor,
                                             const QModelIndex &index) const
{
    if(!index.isValid())
    {
        QStyledItemDelegate::setEditorData(editor, index);
        return;
    }

    if(index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionZ)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleZ)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationW)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationZ))
    {
        QDoubleSpinBox *wid = static_cast<QDoubleSpinBox*>(editor);
        bool ok = false;
        double value = index.data(Qt::EditRole).toDouble(&ok);
        wid->setValue(value);
        wid->setWhatsThis(index.data(Qt::WhatsThisRole).toString());
        wid->setToolTip(index.data(Qt::ToolTipRole).toString());
        wid->setStatusTip(index.data(Qt::StatusTipRole).toString());
        return;
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void FDQUI::TransformDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                            const QModelIndex &index) const
{
    if(!index.isValid())
    {
        QStyledItemDelegate::setEditorData(editor, index);
        return;
    }

    if(index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::PositionZ)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::ScaleZ)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationW)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationX)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationY)
       || index.internalId() == static_cast<quintptr>(TransformModel::InternalId::RotationZ))
    {
        QDoubleSpinBox *wid = static_cast<QDoubleSpinBox*>(editor);
        wid->interpretText();
        double value = wid->value();

        model->setData(index, value, Qt::EditRole);
        return;
    }

    QStyledItemDelegate::setModelData(editor, model, index);
}

void FDQUI::TransformDelegate::updateEditorGeometry(QWidget *editor,
                                                    const QStyleOptionViewItem &option,
                                                    const QModelIndex &index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}
