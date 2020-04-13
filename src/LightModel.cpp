#include <FDQUI/Model/LightModel.h>

#include <QColor>

static bool variantToFloat(const QVariant &value, float &f)
{
    bool ok = false;
    float v = value.toFloat(&ok);
    if(!ok)
        return false;

    f = v;
    return true;
}

static bool variantToColor(const QVariant &value, glm::vec4 &v)
{
    if(!value.canConvert(QMetaType::QColor))
        return false;

    glm::ivec4 iv(v * 255.0f);
    QColor c(iv.r, iv.g, iv.b, iv.a);
    c = value.value<QColor>();
        return false;

    v.r = c.red() / 255.0f;
    v.g = c.green() / 255.0f;
    v.b = c.blue() / 255.0f;
    v.a = c.alpha() / 255.0f;
    return true;
}


FDQUI::LightModel::LightModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_light(nullptr)
{}

QModelIndex FDQUI::LightModel::index(int row, int column, const QModelIndex &parent) const
{
    if(m_light == nullptr)
        return QModelIndex();

    if(!parent.isValid())
        return createIndex(row, column, static_cast<quintptr>(InternalId::Light));

    InternalId id = static_cast<InternalId>(parent.internalId());
    switch(id)
    {
        case InternalId::Unknown:
        case InternalId::LightType:
        case InternalId::LightColorAmbientR:
        case InternalId::LightColorAmbientG:
        case InternalId::LightColorAmbientB:
        case InternalId::LightColorAmbientA:
        case InternalId::LightColorDiffuseR:
        case InternalId::LightColorDiffuseG:
        case InternalId::LightColorDiffuseB:
        case InternalId::LightColorDiffuseA:
        case InternalId::LightColorSpecularR:
        case InternalId::LightColorSpecularG:
        case InternalId::LightColorSpecularB:
        case InternalId::LightColorSpecularA:
        case InternalId::LightConeInnerAngle:
        case InternalId::LightConeOuterAngle:
        case InternalId::LightAttenuationConstant:
        case InternalId::LightAttenuationLinear:
        case InternalId::LightAttenuationQuadratic:
        case InternalId::PositionX:
        case InternalId::PositionY:
        case InternalId::PositionZ:
        case InternalId::DirectionX:
        case InternalId::DirectionY:
        case InternalId::DirectionZ:
        case InternalId::UpVectorX:
        case InternalId::UpVectorY:
        case InternalId::UpVectorZ:
        return QModelIndex();

        case InternalId::Light:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::LightType;
                break;

                case 1:
                childId = InternalId::LightColor;
                break;

                case 2:
                childId = InternalId::LightCone;
                break;

                case 3:
                childId = InternalId::LightAttenuation;
                break;

                case 4:
                childId = InternalId::Position;
                break;

                case 5:
                childId = InternalId::Direction;
                break;

                case 6:
                childId = InternalId::UpVector;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::LightCone:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::LightConeInnerAngle;
                break;

                case 1:
                childId = InternalId::LightConeOuterAngle;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::LightAttenuation:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::LightAttenuationConstant;
                break;

                case 1:
                childId = InternalId::LightAttenuationLinear;
                break;

                case 2:
                childId = InternalId::LightAttenuationQuadratic;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::LightColor:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::LightColorAmbient;
                break;

                case 1:
                childId = InternalId::LightColorDiffuse;
                break;

                case 2:
                childId = InternalId::LightColorSpecular;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::LightColorAmbient:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::LightColorAmbientR;
                break;

                case 1:
                childId = InternalId::LightColorAmbientG;
                break;

                case 2:
                childId = InternalId::LightColorAmbientB;
                break;

                case 3:
                childId = InternalId::LightColorAmbientA;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::LightColorDiffuse:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::LightColorDiffuseR;
                break;

                case 1:
                childId = InternalId::LightColorDiffuseG;
                break;

                case 2:
                childId = InternalId::LightColorDiffuseB;
                break;

                case 3:
                childId = InternalId::LightColorDiffuseA;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::LightColorSpecular:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::LightColorSpecularR;
                break;

                case 1:
                childId = InternalId::LightColorSpecularG;
                break;

                case 2:
                childId = InternalId::LightColorSpecularB;
                break;

                case 3:
                childId = InternalId::LightColorSpecularA;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::Position:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::PositionX;
                break;

                case 1:
                childId = InternalId::PositionY;
                break;

                case 2:
                childId = InternalId::PositionZ;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::Direction:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::DirectionX;
                break;

                case 1:
                childId = InternalId::DirectionY;
                break;

                case 2:
                childId = InternalId::DirectionZ;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }

        case InternalId::UpVector:
        {
            InternalId childId = InternalId::Unknown;
            switch(row)
            {
                case 0:
                childId = InternalId::UpVectorX;
                break;

                case 1:
                childId = InternalId::UpVectorY;
                break;

                case 2:
                childId = InternalId::UpVectorZ;
                break;

                default:
                break;
            }

            return createIndex(row, column, static_cast<quintptr>(childId));
        }
    }

    return QModelIndex();
}

QModelIndex FDQUI::LightModel::parent(const QModelIndex &index) const
{
    if(m_light == nullptr || !index.isValid())
        return QModelIndex();

    switch(static_cast<InternalId>(index.internalId()))
    {
        case InternalId::Unknown:
        case InternalId::Light:
        return QModelIndex();

        case InternalId::LightType:
        case InternalId::LightColor:
        case InternalId::LightCone:
        case InternalId::LightAttenuation:
        case InternalId::Position:
        case InternalId::Direction:
        case InternalId::UpVector:
        return createIndex(0, 0, static_cast<quintptr>(InternalId::Light));

        case InternalId::LightColorAmbient:
        case InternalId::LightColorDiffuse:
        case InternalId::LightColorSpecular:
        return createIndex(1, 0, static_cast<quintptr>(InternalId::LightColor));

        case InternalId::LightConeInnerAngle:
        case InternalId::LightConeOuterAngle:
        return createIndex(2, 0, static_cast<quintptr>(InternalId::LightCone));

        case InternalId::LightAttenuationConstant:
        case InternalId::LightAttenuationLinear:
        case InternalId::LightAttenuationQuadratic:
        return createIndex(3, 0, static_cast<quintptr>(InternalId::LightAttenuation));

        case InternalId::PositionX:
        case InternalId::PositionY:
        case InternalId::PositionZ:
        return createIndex(4, 0, static_cast<quintptr>(InternalId::Position));

        case InternalId::DirectionX:
        case InternalId::DirectionY:
        case InternalId::DirectionZ:
        return createIndex(5, 0, static_cast<quintptr>(InternalId::Direction));

        case InternalId::UpVectorX:
        case InternalId::UpVectorY:
        case InternalId::UpVectorZ:
        return createIndex(6, 0, static_cast<quintptr>(InternalId::UpVector));

        case InternalId::LightColorAmbientR:
        case InternalId::LightColorAmbientG:
        case InternalId::LightColorAmbientB:
        case InternalId::LightColorAmbientA:
        return createIndex(0, 0, static_cast<quintptr>(InternalId::LightColorAmbient));

        case InternalId::LightColorDiffuseR:
        case InternalId::LightColorDiffuseG:
        case InternalId::LightColorDiffuseB:
        case InternalId::LightColorDiffuseA:
        return createIndex(1, 0, static_cast<quintptr>(InternalId::LightColorDiffuse));

        case InternalId::LightColorSpecularR:
        case InternalId::LightColorSpecularG:
        case InternalId::LightColorSpecularB:
        case InternalId::LightColorSpecularA:
        return createIndex(2, 0, static_cast<quintptr>(InternalId::LightColorSpecular));
    }

    return QModelIndex();
}

int FDQUI::LightModel::rowCount(const QModelIndex &parent) const
{
    if(m_light == nullptr)
        return 0;

    if(!parent.isValid())
        return 1;

    switch(static_cast<InternalId>(parent.internalId()))
    {
        case InternalId::Unknown:
        return 0;

        case InternalId::Light:
        return 7;

        case InternalId::LightType:
        return 1;

        case InternalId::LightCone:
        return 2;

        case InternalId::LightColor:
        case InternalId::LightAttenuation:
        case InternalId::Position:
        case InternalId::Direction:
        case InternalId::UpVector:
        return 3;

        case InternalId::LightColorAmbient:
        case InternalId::LightColorDiffuse:
        case InternalId::LightColorSpecular:
        return 4;

        default:
        return 0;
    }
}

int FDQUI::LightModel::columnCount(const QModelIndex &) const
{
    return 1;
}

bool FDQUI::LightModel::hasChildren(const QModelIndex &parent) const
{
    if(!parent.isValid())
        return true;

    switch(static_cast<InternalId>(parent.internalId()))
    {
        case InternalId::Unknown:
        case InternalId::Light:
        case InternalId::LightType:
        case InternalId::LightColor:
        case InternalId::LightCone:
        case InternalId::LightAttenuation:
        case InternalId::Position:
        case InternalId::Direction:
        case InternalId::UpVector:
        case InternalId::LightColorAmbient:
        case InternalId::LightColorDiffuse:
        case InternalId::LightColorSpecular:
        case InternalId::LightConeInnerAngle:
        case InternalId::LightConeOuterAngle:
        case InternalId::LightAttenuationConstant:
        case InternalId::LightAttenuationLinear:
        case InternalId::LightAttenuationQuadratic:
        return true;

        case InternalId::PositionX:
        case InternalId::PositionY:
        case InternalId::PositionZ:
        case InternalId::DirectionX:
        case InternalId::DirectionY:
        case InternalId::DirectionZ:
        case InternalId::UpVectorX:
        case InternalId::UpVectorY:
        case InternalId::UpVectorZ:
        case InternalId::LightColorAmbientR:
        case InternalId::LightColorAmbientG:
        case InternalId::LightColorAmbientB:
        case InternalId::LightColorAmbientA:
        case InternalId::LightColorDiffuseR:
        case InternalId::LightColorDiffuseG:
        case InternalId::LightColorDiffuseB:
        case InternalId::LightColorDiffuseA:
        case InternalId::LightColorSpecularR:
        case InternalId::LightColorSpecularG:
        case InternalId::LightColorSpecularB:
        case InternalId::LightColorSpecularA:
        return false;
    }

    return false;
}

QVariant FDQUI::LightModel::data(const QModelIndex &index, int role) const
{
    if(m_light == nullptr || !index.isValid())
        return QVariant();

    switch(static_cast<InternalId>(index.internalId()))
    {
        case InternalId::Light:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light");
        }
        break;

        case InternalId::LightType:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
            {
                switch(m_light->getType())
                {
                    case FD3D::LightType::AreaLight:
                    return tr("Area Light");

                    case FD3D::LightType::PointLight:
                    return tr("Point Light");

                    case FD3D::LightType::DirectionalLight:
                    return tr("Directional Light");

                    case FD3D::LightType::AmbientLight:
                    return tr("Ambient Light");

                    case FD3D::LightType::SpotLight:
                    return tr("Spot Light");

                    case FD3D::LightType::Undefined:
                    return tr("Undefined Light Type");
                }
            }
        }
        break;

        case InternalId::LightColor:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Color");
        }
        break;

        case InternalId::LightCone:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Cone");
        }
        break;

        case InternalId::LightAttenuation:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Attenuation");
        }
        break;

        case InternalId::Position:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Position");
        }
        break;

        case InternalId::Direction:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Direction");
        }
        break;

        case InternalId::UpVector:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Up Vector");
        }
        break;

        case InternalId::LightColorAmbient:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Ambient Color");

            if(role == Qt::EditRole)
            {
                glm::vec4 &col = m_light->color.ambient;
                glm::ivec4 tmp = col * 255.0f;
                return QColor(tmp.r, tmp.g, tmp.b, tmp.a);
            }
        }
        break;

        case InternalId::LightColorDiffuse:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Diffuse Color");

            if(role == Qt::EditRole)
            {
                glm::vec4 &col = m_light->color.diffuse;
                glm::ivec4 tmp = col * 255.0f;
                return QColor(tmp.r, tmp.g, tmp.b, tmp.a);
            }
        }
        break;

        case InternalId::LightColorSpecular:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Specular Color");

            if(role == Qt::EditRole)
            {
                glm::vec4 &col = m_light->color.specular;
                glm::ivec4 tmp = col * 255.0f;
                return QColor(tmp.r, tmp.g, tmp.b, tmp.a);
            }
        }
        break;

        case InternalId::LightConeInnerAngle:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Cone Inner Angle");
        }
        break;

        case InternalId::LightConeOuterAngle:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Cone Outer Angle");
        }
        break;

        case InternalId::LightAttenuationConstant:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Constant Attenuation");
        }
        break;

        case InternalId::LightAttenuationLinear:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Linear Attenuation");
        }
        break;

        case InternalId::LightAttenuationQuadratic:
        {
            if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Linear Attenuation");
        }
        break;

        case InternalId::PositionX:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Position x");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getPosition().x;
        }
        break;

        case InternalId::PositionY:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Position y");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getPosition().y;
        }
        break;

        case InternalId::PositionZ:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Position z");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getPosition().z;
        }
        break;

        case InternalId::DirectionX:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Direction x");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getDirection().x;
        }
        break;

        case InternalId::DirectionY:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Direction y");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getDirection().y;
        }
        break;

        case InternalId::DirectionZ:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Direction z");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getDirection().z;
        }
        break;

        case InternalId::UpVectorX:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Up Vector x");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getUp().x;
        }
        break;

        case InternalId::UpVectorY:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Up Vector y");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getUp().y;
        }
        break;

        case InternalId::UpVectorZ:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Up Vector z");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->getUp().z;
        }
        break;

        case InternalId::LightColorAmbientR:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Ambient Color r");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.ambient.r;
        }
        break;

        case InternalId::LightColorAmbientG:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Ambient Color g");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.ambient.g;
        }
        break;

        case InternalId::LightColorAmbientB:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Ambient Color b");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.ambient.b;
        }
        break;

        case InternalId::LightColorAmbientA:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Ambient Color a");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.ambient.a;
        }
        break;

        case InternalId::LightColorDiffuseR:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Diffuse Color r");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.diffuse.r;
        }
        break;

        case InternalId::LightColorDiffuseG:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Diffuse Color g");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.diffuse.g;
        }
        break;

        case InternalId::LightColorDiffuseB:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Diffuse Color b");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.diffuse.b;
        }
        break;

        case InternalId::LightColorDiffuseA:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Diffuse Color a");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.diffuse.a;
        }
        break;

        case InternalId::LightColorSpecularR:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Specular Color r");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.specular.r;
        }
        break;

        case InternalId::LightColorSpecularG:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Specular Color g");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.specular.g;
        }
        break;

        case InternalId::LightColorSpecularB:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Specular Color b");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.specular.b;
        }
        break;

        case InternalId::LightColorSpecularA:
        {
            if(role == Qt::ToolTipRole || role == Qt::WhatsThisRole)
                return tr("Light Specular Color a");

            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return m_light->color.specular.a;
        }
        break;

        case InternalId::Unknown:
        return QVariant();
    }

    return QVariant();
}

bool FDQUI::LightModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(m_light == nullptr || !index.isValid())
        return false;

    switch(static_cast<InternalId>(index.internalId()))
    {
        case InternalId::LightType:
        {
            if(role == Qt::EditRole)
            {
                bool ok = false;
                int v = value.toInt(&ok);
                if(!ok || v > 5)
                    return false;

                m_light->setType(static_cast<FD3D::LightType>(v));
                return true;
            }
        }
        break;

        case InternalId::PositionX:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getPosition().x);
        }
        break;

        case InternalId::PositionY:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getPosition().y);
        }
        break;

        case InternalId::PositionZ:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getPosition().z);
        }
        break;

        case InternalId::DirectionX:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getDirection().x);
        }
        break;

        case InternalId::DirectionY:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getDirection().y);
        }
        break;

        case InternalId::DirectionZ:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getDirection().z);
        }
        break;

        case InternalId::UpVectorX:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getUp().x);
        }
        break;

        case InternalId::UpVectorY:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getUp().y);
        }
        break;

        case InternalId::UpVectorZ:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->getUp().z);
        }
        break;

        case InternalId::LightColorAmbientR:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.ambient.r);
        }
        break;

        case InternalId::LightColorAmbientG:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.ambient.g);
        }
        break;

        case InternalId::LightColorAmbientB:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.ambient.b);
        }
        break;

        case InternalId::LightColorAmbientA:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.ambient.a);
        }
        break;

        case InternalId::LightColorDiffuseR:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.diffuse.r);
        }
        break;

        case InternalId::LightColorDiffuseG:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.diffuse.g);
        }
        break;

        case InternalId::LightColorDiffuseB:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.diffuse.b);
        }
        break;

        case InternalId::LightColorDiffuseA:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.diffuse.a);
        }
        break;

        case InternalId::LightColorSpecularR:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.specular.r);
        }
        break;

        case InternalId::LightColorSpecularG:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.specular.g);
        }
        break;

        case InternalId::LightColorSpecularB:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.specular.b);
        }
        break;

        case InternalId::LightColorSpecularA:
        {
            if(role == Qt::EditRole)
                return variantToFloat(value, m_light->color.specular.a);
        }
        break;

        case InternalId::LightColorAmbient:
        {
            if(role == Qt::EditRole)
                return variantToColor(value, m_light->color.ambient);
        }
        break;

        case InternalId::LightColorDiffuse:
        {
            if(role == Qt::EditRole)
                return variantToColor(value, m_light->color.diffuse);
        }
        break;

        case InternalId::LightColorSpecular:
        {
            if(role == Qt::EditRole)
                return variantToColor(value, m_light->color.specular);
        }
        break;

        case InternalId::Unknown:
        case InternalId::Light:
        case InternalId::LightColor:
        case InternalId::LightCone:
        case InternalId::LightAttenuation:
        case InternalId::Position:
        case InternalId::Direction:
        case InternalId::UpVector:
        case InternalId::LightConeInnerAngle:
        case InternalId::LightConeOuterAngle:
        case InternalId::LightAttenuationConstant:
        case InternalId::LightAttenuationLinear:
        case InternalId::LightAttenuationQuadratic:
        return false;
    }

    return false;
}

Qt::ItemFlags FDQUI::LightModel::flags(const QModelIndex &index) const
{
    if(m_light == nullptr || !index.isValid())
        return Qt::NoItemFlags;;

    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled;

    switch(static_cast<InternalId>(index.internalId()))
    {
        case InternalId::LightColorAmbient:
        case InternalId::LightColorDiffuse:
        case InternalId::LightColorSpecular:
        result |= Qt::ItemIsDropEnabled | Qt::ItemIsEditable;
        break;

        case InternalId::LightType:
        case InternalId::PositionX:
        case InternalId::PositionY:
        case InternalId::PositionZ:
        case InternalId::DirectionX:
        case InternalId::DirectionY:
        case InternalId::UpVectorX:
        case InternalId::UpVectorY:
        case InternalId::UpVectorZ:
        case InternalId::LightColorAmbientR:
        case InternalId::LightColorAmbientG:
        case InternalId::LightColorAmbientB:
        case InternalId::LightColorAmbientA:
        case InternalId::LightColorDiffuseR:
        case InternalId::LightColorDiffuseG:
        case InternalId::LightColorDiffuseB:
        case InternalId::LightColorDiffuseA:
        case InternalId::LightColorSpecularR:
        case InternalId::LightColorSpecularG:
        case InternalId::LightColorSpecularB:
        case InternalId::LightColorSpecularA:
        result |= Qt::ItemIsDropEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
        break;

        default:
        break;
    }

    return result;
}

FD3D::Light *FDQUI::LightModel::getLight()
{
    return m_light;
}

const FD3D::Light *FDQUI::LightModel::getLight() const
{
    return m_light;
}

void FDQUI::LightModel::setLight(FD3D::Light *light)
{
    m_light = light;
}
