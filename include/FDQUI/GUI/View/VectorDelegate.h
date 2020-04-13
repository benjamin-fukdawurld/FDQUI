#ifndef VECTORDELEGATE_H
#define VECTORDELEGATE_H

#include <QStyledItemDelegate>

namespace FDQUI
{
    class VectorDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

        public:
            VectorDelegate(QObject *parent = nullptr);

            QWidget *createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;

            void setEditorData(QWidget *editor, const QModelIndex &index) const override;
            void setModelData(QWidget *editor,
                              QAbstractItemModel *model,
                              const QModelIndex &index) const override;
    };
}
#endif // VECTORDELEGATE_H
