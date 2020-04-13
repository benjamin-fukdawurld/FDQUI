#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

#include <FDQUI/Model/ColorModel.h>


namespace FDQUI
{
    class ColorWidget : public QWidget
    {
        Q_OBJECT
        protected:
            ColorModel m_model;

        public:
            explicit ColorWidget(QWidget *parent = nullptr);

        signals:

        public slots:
    };
}

#endif // COLORWIDGET_H
