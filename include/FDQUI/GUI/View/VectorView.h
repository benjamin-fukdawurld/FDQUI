#ifndef VIEWVECTORVIEW_H
#define VIEWVECTORVIEW_H

#include <QAbstractItemView>

#include <FDQUI/Model/MatriceModel.h>

#include <QDoubleSpinBox>
#include <QStyledItemDelegate>
#include <QLabel>
#include <QList>

namespace FDQUI
{
    class VectorView : public QAbstractItemView
    {
        Q_OBJECT
        protected:
            QList<QLabel*> m_labels;
            QList<QWidget*> m_widgets;
            int m_column;

        public:
            explicit VectorView(QWidget *parent = nullptr);
            int getColumn();

            QModelIndex	indexAt(const QPoint &point) const override;
            void scrollTo(const QModelIndex &index,
                          QAbstractItemView::ScrollHint hint = EnsureVisible) override;
            QRect visualRect(const QModelIndex &index) const override;

        protected:
            int horizontalOffset() const override;
            int verticalOffset() const override;
            bool isIndexHidden(const QModelIndex &index) const override;
            QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                                   Qt::KeyboardModifiers modifiers) override;
            void setSelection(const QRect &rect,
                              QItemSelectionModel::SelectionFlags flags) override;
            QRegion visualRegionForSelection(const QItemSelection &selection) const override;

        signals:
            void modelChanged(QAbstractItemModel *);
            void columnChanged(int);

        public slots:
            void setModel(QAbstractItemModel *model) override;
            void setColumn(int column);

        protected slots:
            virtual void lay();
            virtual void clearWidgets();
    };
}

#endif // VIEWVECTORVIEW_H
