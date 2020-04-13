#include <FDQUI/GUI/Widget/OpenGLWidget.h>
#include <FDQUI/GUI/OpenGLApplication.h>

#include <FDGL/OpenGLUtils.h>

#include <QOpenGLContext>

#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <GLFW/glfw3.h>

using namespace std;

std::string loadFile(const std::string &filePath)
{
    FILE* f = fopen(filePath.c_str(), "r");
    if(!f)
        throw runtime_error(filePath + ": not found");

    // Determine file size
    fseek(f, 0, SEEK_END);
    size_t size = static_cast<size_t>(ftell(f));

    std::unique_ptr<char[]> where(new char[size]);

    rewind(f);
    fread(where.get(), sizeof(char), size, f);
    std::string result(where.get(), size);

    return result;
}

FDGL::OpenGLTextureWrapper loadTexture(const std::string &filePath)
{
    size_t size[2];
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    std::unique_ptr<unsigned char, void (*)(unsigned char*)> data(stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0),
                                                                  [](unsigned char *data) { stbi_image_free(data); });
    size[0] = static_cast<size_t>(width);
    size[1] = static_cast<size_t>(height);

    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return FDGL::OpenGLTextureWrapper();
    }

    FDGL::OpenGLTextureWrapper tex;
    if(!tex.create())
        return FDGL::OpenGLTextureWrapper();

    tex.bind(FDGL::TextureTarget::Texture2D);

    tex.setWrapModeS(FDGL::TextureWrapMode::Repeat);
    tex.setWrapModeT(FDGL::TextureWrapMode::Repeat);

    tex.setMinFilter(FDGL::TextureFilter::LinearMipmapLinear);
    tex.setMagFilter(FDGL::TextureFilter::Linear);

    GLenum format;
    switch (nrChannels)
    {
        case 1:
            format = GL_RED;
        break;

        case 2:
            format = GL_RG;
        break;

        case 3:
            format = GL_RGB;
        break;

        case 4:
            format = GL_RGBA;
        break;

        default:
            format = GL_INVALID_ENUM;
        break;
    }

    tex.allocate(FDGL::TextureTarget::Texture2D, 0, GL_RGBA, size,  format,
                 GL_UNSIGNED_BYTE, data.get());
    //tex.generateMipMap();

    return tex;
}

FDGL::OpenGLTextureWrapper loadTexture(const aiTexture *input)
{
    FDGL::OpenGLTextureWrapper tex;
    if(!tex.create())
        return FDGL::OpenGLTextureWrapper();

    size_t size[2];
    size[0] = static_cast<size_t>(input->mWidth);
    size[1] = static_cast<size_t>(input->mHeight);
    std::string formatStr(input->achFormatHint);
    GLenum format;
    if(formatStr == "rgba8888" || formatStr == "argb8888" || formatStr == "png")
    {
        format = GL_RGBA;
    }
    else if(formatStr == "jpg")
    {
        format = GL_RGB;
    }
    else if(formatStr == "rgba0010")
    {
        format = GL_RED;
    }
    else
    {
        std::cerr << "unsupported texture format '" << formatStr << "'" << std::endl;
        return FDGL::OpenGLTextureWrapper();
    }

    tex.bind(FDGL::TextureTarget::Texture2D);

    tex.setWrapModeS(FDGL::TextureWrapMode::Repeat);
    tex.setWrapModeT(FDGL::TextureWrapMode::Repeat);

    tex.setMinFilter(FDGL::TextureFilter::LinearMipmapLinear);
    tex.setMagFilter(FDGL::TextureFilter::Linear);
    tex.allocate(FDGL::TextureTarget::Texture2D, 0, GL_RGBA, size,  format,
                 GL_UNSIGNED_BYTE, reinterpret_cast<void*>(input->pcData));
    tex.generateMipMap();

    return tex;
}

FDGL::OpenGLShaderProgramWrapper createShaderProgram()
{
    FDGL::OpenGLShaderProgramWrapper program;
    FDGL::OpenGLShader v_shad;
    v_shad.create(FDGL::ShaderType::Vertex);
    v_shad.setSource(loadFile("../../FDGL/test/resources/vertex.vert"));
    if(!v_shad.compile())
    {
        std::string msg = "Cannot compile vertex shader: ";
        msg += v_shad.getCompileErrors();
        cerr << msg << endl;
        return FDGL::OpenGLShaderProgramWrapper();
    }

    FDGL::OpenGLShader f_shad;
    f_shad.create(FDGL::ShaderType::Fragment);
    f_shad.setSource(loadFile("../../FDGL/test/resources/frag.frag"));
    if(!f_shad.compile())
    {
        std::string msg = "Cannot compile fragment shader: ";
        msg += f_shad.getCompileErrors();
        cerr << msg << endl;
        return FDGL::OpenGLShaderProgramWrapper();
    }

    // link shaders
    program.create();
    program.attach(v_shad);
    program.attach(f_shad);
    if(!program.link())
    {
        std::string msg = "Cannot link shader program: ";
        msg += program.getLinkErrors();
        cerr << msg << endl;
        return FDGL::OpenGLShaderProgramWrapper();
    }

    return program;
}

FDQUI::OpenGLWidget::OpenGLWidget(QWidget *parent, Qt::WindowFlags f) :
    QOpenGLWidget(parent, f),
    FDGL::BaseOpenGLWindow ()
{

}

FDQUI::OpenGLWidget::~OpenGLWidget()
{
    destroy();
}

bool FDQUI::OpenGLWidget::create(int width, int height, const std::string &title)
{
    setMinimumSize(width, height);
    QOpenGLWidget::resize(width, height);
    QOpenGLWidget::setObjectName(title.c_str());

    return true;
}

void FDQUI::OpenGLWidget::destroy()
{
    if(m_quitStrategy)
        m_quitStrategy(*this);
}

bool FDQUI::OpenGLWidget::isOpen() const
{
    return QOpenGLWidget::isVisible();
}

void FDQUI::OpenGLWidget::swapBuffer() const
{
    this->context()->swapBuffers(context()->surface());
}

std::string FDQUI::OpenGLWidget::getTitle() const
{
    return  objectName().toUtf8().data();
}

void FDQUI::OpenGLWidget::setTitle(const std::string &title)
{
    QOpenGLWidget::setObjectName(title.c_str());
}

int FDQUI::OpenGLWidget::getWidth() const
{
    return width();
}

void FDQUI::OpenGLWidget::setWidth(int w)
{
    QOpenGLWidget::resize(w, height());
}

int FDQUI::OpenGLWidget::getHeight() const
{
    return height();
}

void FDQUI::OpenGLWidget::setHeight(int h)
{
    QOpenGLWidget::resize(width(), h);
}

void FDQUI::OpenGLWidget::initializeGL()
{
    if(m_initStrategy)
        m_initStrategy(*this);
}

void FDQUI::OpenGLWidget::paintGL()
{
    if(m_renderStrategy)
        m_renderStrategy(*this);
}

void FDQUI::OpenGLWidget::resizeGL(int w, int h)
{
    if(m_resizeStrategy)
        m_resizeStrategy(*this, w, h);
}

