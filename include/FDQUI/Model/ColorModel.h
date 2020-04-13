#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <glm/vec4.hpp>

#include <QAbstractItemModel>

class ColorModel : public QAbstractItemModel
{
    Q_OBJECT
    protected:
        glm::vec4 *m_color;

        enum class InternalId: uint8_t
        {
            Color,
            Red,
            Green,
            Blue,
            Alpha
        };

    public:
        explicit ColorModel(QObject *parent = nullptr);

        ~ColorModel() override = default;

        const glm::vec4 *getColor() const;
        glm::vec4 *getColor();

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

        bool setData(
                const QModelIndex &index,
                const QVariant &value,
                int role = Qt::EditRole
            ) override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;

    public slots:
        void setColor(glm::vec4 *color);

        void unsetColor();
};

#endif // COLORMODEL_H
