#ifndef VECTORWIDGET_H
#define VECTORWIDGET_H

#include <FDQUI/GUI/View/VectorView.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace FDQUI
{
    class VectorWidget : public VectorView
    {
        Q_OBJECT
        public:
            explicit VectorWidget(QWidget *parent = nullptr);

            ~VectorWidget() override = default;

            template<int C, int R>
            void setMatrix(glm::mat<C, R, float, glm::defaultp> &mat)
            {
                setValues(glm::value_ptr(mat), static_cast<int>(R));
                setColumn(C);
            }

            template<int S>
            void setVector(glm::vec<S, float, glm::defaultp> &v)
            {
                setValues(glm::value_ptr(v), static_cast<size_t>(S));
            }

            void setQuaternion(glm::quat &q)
            {
                setValues(glm::value_ptr(q), 4);
            }

        signals:
            void vectorChanged(float *);
            void numberOfComponentsChanged(size_t);

        public slots:
            void setValues(float *vector, size_t nbComponents);

            void unsetValues() { setValues(nullptr, 0); }
    };
}

#endif // VECTORWIDGET_H
