#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include <QAbstractItemModel>

#include <FD3D/Light/Light.h>

namespace FDQUI
{
    class LightModel : public QAbstractItemModel
    {
            Q_OBJECT
        protected:
            FD3D::Light *m_light;

            enum class InternalId: uint8_t
            {
                Unknown,
                Light,
                LightType,
                LightColor,
                LightColorAmbient,
                LightColorAmbientR,
                LightColorAmbientG,
                LightColorAmbientB,
                LightColorAmbientA,
                LightColorDiffuse,
                LightColorDiffuseR,
                LightColorDiffuseG,
                LightColorDiffuseB,
                LightColorDiffuseA,
                LightColorSpecular,
                LightColorSpecularR,
                LightColorSpecularG,
                LightColorSpecularB,
                LightColorSpecularA,
                LightCone,
                LightConeInnerAngle,
                LightConeOuterAngle,
                LightAttenuation,
                LightAttenuationConstant,
                LightAttenuationLinear,
                LightAttenuationQuadratic,
                Position,
                PositionX,
                PositionY,
                PositionZ,
                Direction,
                DirectionX,
                DirectionY,
                DirectionZ,
                UpVector,
                UpVectorX,
                UpVectorY,
                UpVectorZ
            };

        public:
            LightModel(QObject *parent = nullptr);

            ~LightModel() override = default;

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

            FD3D::Light *getLight();

            const FD3D::Light *getLight() const;

            void setLight(FD3D::Light *light);

            void unsetLight() { setLight(nullptr); }
    };
}

#endif // LIGHTMODEL_H
