#ifndef TRANSFORMMODEL_H
#define TRANSFORMMODEL_H

#include <QAbstractItemModel>

class TransformModel : public QAbstractItemModel
{
    Q_OBJECT
    protected:


    public:
        TransformModel(QObject *parent = nullptr);

        ~TransformModel() override = default;
};

#endif // TRANSFORMMODEL_H
