#include "include/FDQUI/GUI/Widget/VectorWidget.h"

#include <FDQUI/Model/MatriceModel.h>

FDQUI::VectorWidget::VectorWidget(QWidget *parent) : VectorView(parent)
{
    setModel(new FDQUI::MatriceModel());
}

void FDQUI::VectorWidget::setValues(float *vector, size_t nbComponents)
{
    emit vectorChanged(vector);
    emit numberOfComponentsChanged(nbComponents);
    static_cast<FDQUI::MatriceModel*>(model())->setValues(vector, nbComponents, 1);
}
