#include <FDQUI/GUI/View/VectorView.h>
#include <FDQUI/GUI/View/VectorDelegate.h>

#include <QHBoxLayout>
#include <QFormLayout>

FDQUI::VectorView::VectorView(QWidget *parent) :
    QAbstractItemView(parent),
    m_column(0)
{
    setItemDelegate(new VectorDelegate(this));
    connect(this, &FDQUI::VectorView::modelChanged, this, &FDQUI::VectorView::lay);
}

int FDQUI::VectorView::getColumn()
{
    return m_column;
}

QModelIndex FDQUI::VectorView::indexAt(const QPoint &point) const
{
    QWidget *wid = childAt(point);
    if(wid == nullptr)
        return QModelIndex();

    int row = m_widgets.indexOf(wid);
    return model()->index(row, m_column, rootIndex());
}

void FDQUI::VectorView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint /*hint*/)
{
    setColumn(index.column());
}

QRect FDQUI::VectorView::visualRect(const QModelIndex &index) const
{
    if(!index.isValid() || index.parent() != rootIndex()
       || index.row() >= m_widgets.size()
       || index.column() != m_column)
        return QRect();

    return m_widgets[index.row()]->rect();
}

int FDQUI::VectorView::horizontalOffset() const
{
    return 0;
}

int FDQUI::VectorView::verticalOffset() const
{
    return 0;
}

bool FDQUI::VectorView::isIndexHidden(const QModelIndex &index) const
{
    return m_column != index.column();
}

QModelIndex FDQUI::VectorView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers /*modifiers*/)
{
    switch (cursorAction)
    {
        case QAbstractItemView::MoveUp:
        case QAbstractItemView::MovePageUp:
        {
            QModelIndex index = currentIndex();
            return model()->index(index.row(), index.column() - 1, index.parent());
        }

        case QAbstractItemView::MoveDown:
        case QAbstractItemView::MovePageDown:
        {
            QModelIndex index = currentIndex();
            return model()->index(index.row(), index.column() + 1, index.parent());
        }

        case QAbstractItemView::MoveHome:
        return model()->index(0, 0, rootIndex());

        case QAbstractItemView::MoveEnd:
        return model()->index(model()->rowCount() - 1, model()->columnCount() - 1, rootIndex());

        case QAbstractItemView::MoveLeft:
        case QAbstractItemView::MoveNext:
        {
            QModelIndex index = currentIndex();
            return model()->index(index.row() - 1, index.column(), index.parent());
        }

        case QAbstractItemView::MoveRight:
        case QAbstractItemView::MovePrevious:
        {
            QModelIndex index = currentIndex();
            return model()->index(index.row() + 1, index.column(), index.parent());
        }
    }

    return QModelIndex();
}

void FDQUI::VectorView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags)
{
    QItemSelectionModel *m = selectionModel();
    if(m == nullptr)
        return;

    std::vector<QModelIndex> selected;
    for(int i = 0, imax = m_widgets.size(); i < imax; ++i)
    {
        if(rect.intersects(m_widgets[i]->rect()))
            selected.push_back(model()->index(i, m_column, rootIndex()));
    }

    m->select(QItemSelection(selected.front(), selected.back()), flags);
}

QRegion FDQUI::VectorView::visualRegionForSelection(const QItemSelection &/*selection*/) const
{
    return QRegion(rect());
}

void FDQUI::VectorView::setModel(QAbstractItemModel *model)
{
    if(this->model() == model)
        return;

    QAbstractItemView::setModel(model);
    emit modelChanged(model);
}

void FDQUI::VectorView::setColumn(int column)
{
    if(m_column == column)
        return;

    m_column = column;
    emit columnChanged(m_column);
}

void FDQUI::VectorView::lay()
{
    clearWidgets();
    QAbstractItemModel *m = model();
    if(m == nullptr
       || m_column >= m->columnCount(rootIndex()))
        return;

    int imax = m->rowCount(rootIndex());
    m_labels.reserve(imax);
    m_widgets.reserve(imax);
    QHBoxLayout *hlay = new QHBoxLayout();
    for(int i = 0; i < imax; ++i)
    {
        m_labels.append(new QLabel(m->headerData(i, Qt::Vertical).toString()));
        QWidget *wid = itemDelegate()->createEditor(nullptr, QStyleOptionViewItem(), model()->index(i, m_column, rootIndex()));
        hlay->addWidget(m_labels.back());
        hlay->addWidget(wid);
        m_widgets.append(wid);
    }

    setLayout(hlay);
}

void FDQUI::VectorView::clearWidgets()
{
    for(int i = 0, imax = m_labels.size(); i < imax; ++i)
        delete m_labels[i];
    m_labels.clear();

    for(int i = 0, imax = m_widgets.size(); i < imax; ++i)
        delete m_widgets[i];
    m_widgets.clear();
}
