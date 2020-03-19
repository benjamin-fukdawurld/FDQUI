#ifndef TRANSFORMDELEGATE_H
#define TRANSFORMDELEGATE_H

#include <QStyledItemDelegate>

#include <FDQUI/TransformModel.h>

namespace FDQUI
{
    class TransformDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

        public:
            TransformDelegate(QObject *parent = nullptr);

            /*QWidget *createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;

            void setEditorData(QWidget *editor, const QModelIndex &index) const override;
            void setModelData(QWidget *editor,
                              QAbstractItemModel *model,
                              const QModelIndex &index) const override;

            void updateEditorGeometry(QWidget *editor,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const override;*/
    };
}

#endif // TRANSFORMDELEGATE_H
