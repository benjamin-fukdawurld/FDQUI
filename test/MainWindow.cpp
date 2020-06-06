#include <MainWindow.h>

#include <FDCore/FileUtils.h>

#include <FDQUI/GUI/OpenGLApplication.h>
#include <FDQUI/GUI/View/TransformDelegate.h>
#include <FDQUI/GUI/Widget/VectorWidget.h>
#include <FDQUI/Model/TransformModel.h>

#include <QOpenGLTexture>

#include <QDockWidget>
#include <QTimer>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <qlogging.h>

/*
void FDQUI::OpenGLWidget::paintGL()
{
    m_timeMgr.start();


    m_program = createShaderProgram();
    m_tex = loadTexture("../../FDGL/test/resources/wall.jpg");



    m_program.bind();

    FD3D::Projection &proj = m_cam.projection;
    proj.setFov(glm::radians(45.0f));
    proj.setWidth(getWidth());
    proj.setHeight(getHeight());
    proj.setNear(0.1f);
    proj.setFar(100.0f);
    proj.setType(FD3D::ProjectionType::Perspective);

    glClear(getClearMask());
    if(m_renderStrategy)
        m_renderStrategy(*this);

    FD3D::Transform m_transform;
    std::vector<FD3D::Mesh*> meshes = m_scene.getComponentsAs<FD3D::Mesh>();
    FD3D::Projection &proj = m_cam.projection;

    // bind textures on corresponding texture units
    m_tex.activateTexture(0);
    m_tex.bind(FDGL::TextureTarget::Texture2D);

    double t2 = 0;
    float radius = 10.0f;
    float camX = sin(t2) * radius;
    float camZ = cos(t2) * radius;
    m_cam.setPosition(glm::vec3(camX, 0.0f, camZ));
    m_cam.setRotation(glm::vec3(0.0f, t2, 0.0f));

    // activate shader
    m_program.bind();

    m_program.setUniform("texture", 0);
    m_program.setUniform(1, m_cam.getMatrix());
    m_program.setUniform(2, proj.getMatrix());

    m_program.setUniform(0, m_transform.getMatrix());
    m_vao.bind();
    FDGL::drawElements<uint32_t>(FDGL::DrawMode::Triangles, meshes[0]->getNumberOfIndices(), nullptr);

    if (!qApp->loadOpenGLFunctions(qApp->getProcAddressFunc()))
    {
        qFatal("failed to load OpenGl functions");
        qApp->exit(-1);
    }

    qApp->enableDepth();
    qApp->enableFaceCulling();
    qApp->enable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);

    setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_timeMgr.start();

    FD3D::SceneLoader loader;
    loader.setTextureLoader([](const std::string &path){
        return loadTexture(path);
    });
    loader.setEmbeddedTextureLoader([](const aiTexture *texture){
        return loadTexture(texture);
    });
    assert(loader.loadScene(m_scene,
        "../../FDGL/test/resources/crate/CrateModel.obj",
        aiProcess_Triangulate
    ));

    std::vector<FD3D::Mesh*> meshes = m_scene.getComponentsAs<FD3D::Mesh>();
    std::vector<FD3D::Material*> mat = m_scene.getComponentsAs<FD3D::Material>();

    m_program = createShaderProgram();
    m_tex = loadTexture("../../FDGL/test/resources/wall.jpg");

    m_vbo.create();
    m_vbo.bind(FDGL::BufferTarget::VertexAttribute);
    m_vbo.allocate(sizeof(float) * meshes[0]->getNumberOfVertices() * meshes[0]->getVertexSize(),
            FDGL::BufferUsage::StaticDraw, meshes[0]->getVertices());
    m_ebo.create();
    m_ebo.bind(FDGL::BufferTarget::VertexIndex);
    m_ebo.allocate(sizeof(uint32_t) * meshes[0]->getNumberOfIndices(),
            FDGL::BufferUsage::StaticDraw, meshes[0]->getIndices());

    m_vao.create();
    m_vao.setFunction([](FDGL::OpenGLBuffer &vbo, FDGL::OpenGLBuffer &ebo, FD3D::AbstractMesh &m)
    {
        vbo.bind(FDGL::BufferTarget::VertexAttribute);
        ebo.bind(FDGL::BufferTarget::VertexIndex);
        size_t s = m.getStride() * sizeof(float);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(0, s,
            static_cast<size_t>(m.getComponentOffset(FD3D::VertexComponentType::Position)) * sizeof(float));
        FDGL::enableAttrib(0);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(1, s,
            static_cast<size_t>(m.getComponentOffset(FD3D::VertexComponentType::Normal)) * sizeof(float));
        FDGL::enableAttrib(1);
        FDGL::setAttribFromBuffer<GL_FLOAT, 2, false>(2, s,
            static_cast<size_t>(m.getComponentOffset(FD3D::VertexComponentType::Texture)) * sizeof(float));
        FDGL::enableAttrib(2);
    }, std::ref(m_vbo), std::ref(m_ebo), std::ref(*meshes.front()));

    m_program.bind();

    FD3D::Projection &proj = m_cam.projection;
    proj.setFov(glm::radians(45.0f));
    proj.setWidth(getWidth());
    proj.setHeight(getHeight());
    proj.setNear(0.1f);
    proj.setFar(100.0f);
    proj.setType(FD3D::ProjectionType::Perspective);
}*/

using namespace std;

/*static FDGL::OpenGLShaderProgramWrapper createShaderProgram()
{
    FDGL::OpenGLShaderProgramWrapper program;
    FDGL::OpenGLShader v_shad;
    v_shad.create(FDGL::ShaderType::Vertex);
    v_shad.setSource(std::string(FDCore::readFile("../../FDGL/test/resources/vertex.vert").get()));
    if(!v_shad.compile())
    {
        std::string msg = "Cannot compile vertex shader: ";
        msg += v_shad.getCompileErrors();
        cerr << msg << endl;
        return FDGL::OpenGLShaderProgramWrapper();
    }

    FDGL::OpenGLShader f_shad;
    f_shad.create(FDGL::ShaderType::Fragment);
    f_shad.setSource(std::string(FDCore::readFile("../../FDGL/test/resources/frag.frag").get()));
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
}*/

class Renderer
{
    protected:
        FD3D::Camera m_cam;
        QTimer m_rendertimer;
        QOpenGLTexture *m_tex;
        FD3D::Scene m_scene;

        FDGL::OpenGLBuffer m_vbo;
        FDGL::OpenGLBuffer m_ebo;
        FDGL::OpenGLVertexArray m_vao;

    public:
        Renderer();

        void onInit(FDGL::BaseOpenGLWindow &w);
        void onQuit(FDGL::BaseOpenGLWindow &w);
        void onRender(FDGL::BaseOpenGLWindow &w);
        void onResize(FDGL::BaseOpenGLWindow &w, int width, int height);
        void onError(FDGL::ErrorSoure source, FDGL::ErrorType type,
                     uint32_t id, FDGL::ErrorSeverity level,
                     const std::string &msg) const;

    private:
        static void debugCallbackHelper(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar *message,
                                        const void *userParam);
};


static Renderer renderer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   
    prepareGLWidget();
    prepareLeftDock();
}

MainWindow::~MainWindow()
{

}

void MainWindow::prepareGLWidget()
{
    m_glWindow = new FDQUI::OpenGLWidget();
    if(!m_glWindow->create(800, 600, "Test window"))
    {
        qFatal("failed to create window");
        qApp->exit(-1);
    }
    setCentralWidget(m_glWindow);

    /*m_glWindow->setInitializeStrategy(&Renderer::onInit, &renderer);
    m_glWindow->setQuitStrategy(&Renderer::onQuit, &renderer);
    m_glWindow->setRenderStrategy(&Renderer::onRender, &renderer);
    m_glWindow->setResizeStrategy(&Renderer::onResize, &renderer);*/
}

void MainWindow::prepareLeftDock()
{
    QDockWidget *leftDock = new QDockWidget();
    QWidget *wid = new QWidget();

    QVBoxLayout *vlay = new QVBoxLayout();

    QTreeView *view = new QTreeView();
    FDQUI::VectorWidget *vectorWid = new FDQUI::VectorWidget();
    FDQUI::TransformModel *model = new FDQUI::TransformModel(view);

    model->setTranfsorm(&m_transform);
    vectorWid->setVector(m_transform.getPosition());

    view->setHeaderHidden(true);
    view->setModel(model);
    view->setItemDelegate(new FDQUI::TransformDelegate(view));
    vlay->addWidget(view);
    vlay->addWidget(vectorWid);
    wid->setLayout(vlay);
    leftDock->setWidget(wid);

    addDockWidget(Qt::LeftDockWidgetArea, leftDock);
}

























Renderer::Renderer() :
    m_tex(nullptr)
{
    FD3D::Projection &proj = m_cam.projection;
    proj.setFov(glm::radians(45.0f));
    proj.setNear(0.1f);
    proj.setFar(100.0f);
    proj.setType(FD3D::ProjectionType::Perspective);
}

void Renderer::onInit(FDGL::BaseOpenGLWindow &w)
{
    if (!qApp->loadOpenGLFunctions(qApp->getProcAddressFunc()))
    {
        qFatal("failed to load OpenGl functions");
        qApp->exit(-1);
    }

    w.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    w.setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_rendertimer.connect(&m_rendertimer, &QTimer::timeout,
                          static_cast<FDQUI::OpenGLWidget*>(&w),
                          QOverload<>::of(&FDQUI::OpenGLWidget::update));

    qApp->enableDepth();
    qApp->enableFaceCulling();
    qApp->enable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(&Renderer::debugCallbackHelper, this);

    m_rendertimer.start(1000/60);
    m_tex = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_tex->create();
    m_tex->setData(QImage("../../FDGL/test/resources/wall.jpg").mirrored());

    FD3D::SceneLoader loader;
    loader.setTextureLoader([](const std::string &path){
        return QOpenGLTexture(QImage(path.c_str()).mirrored()).textureId();
    });
    loader.setEmbeddedTextureLoader([](const aiTexture *texture){
        QImage img;
        QOpenGLTexture tex(QOpenGLTexture::Target2D);
        if(texture->mHeight == 0)
        {
            if(!img.loadFromData(reinterpret_cast<uint8_t*>(texture->pcData),
                                 static_cast<int>(texture->mWidth),
                                 QString(texture->achFormatHint).toUpper().toStdString().c_str()))
                return 0u;

            tex.setData(img);
        }
        else
        {
            /*QOpenGLTexture::PixelType type = QOpenGLTexture::NoPixelType;
            if(QString(texture->achFormatHint) == "rgba8888"
               || QString(texture->achFormatHint) == "argb8888")
                type = QOpenGLTexture::UInt32_RGBA8;
            else if(QString(texture->achFormatHint) == "rgba5650")
                type = QOpenGLTexture::UInt16_R5G6B5;
            else
                qCritical("Unsupported texture format: %s for texture %s",
                          texture->achFormatHint, texture->mFilename.C_Str());*/

            //tex.setData(0, 0, QOpenGLTexture::RGBA, type, reinterpret_cast<void*>(texture->pcData));
        }

        return tex.textureId();
    });
    assert(loader.loadScene(m_scene,
        "../../FDGL/test/resources/crate/CrateModel.obj",
        aiProcess_Triangulate
    ));
}

void Renderer::onQuit(FDGL::BaseOpenGLWindow &)
{
    delete m_tex;
}

void Renderer::onRender(FDGL::BaseOpenGLWindow &w)
{
    w.clear();
}

void Renderer::onResize(FDGL::BaseOpenGLWindow &, int width, int height)
{
    m_cam.projection.setWidth(width);
    m_cam.projection.setHeight(height);
}

void Renderer::onError(FDGL::ErrorSoure source, FDGL::ErrorType type, uint32_t id,
                       FDGL::ErrorSeverity level, const std::string &msg) const
{
    constexpr const char *format = "GL_DEBUG_MESSAGE:"
                                   "\n{"
                                   "\n    source: %s,"
                                   "\n    type: %s,"
                                   "\n    severity: %s,"
                                   "\n    id: %u"
                                   "\n    message: %s"
                                   "\n}";
    switch(level)
    {
        case FDGL::ErrorSeverity::Low:
            qWarning(format, FDGL::errorSourceToString(source).c_str(),
                     FDGL::errorTypeToString(type).c_str(),
                     FDGL::errorSeverityToString(level).c_str(),
                     id, msg.data());
        break;

        case FDGL::ErrorSeverity::Medium:
            qCritical(format, FDGL::errorSourceToString(source).c_str(),
                      FDGL::errorTypeToString(type).c_str(),
                      FDGL::errorSeverityToString(level).c_str(),
                      id, msg.data());
        break;

        case FDGL::ErrorSeverity::High:
            qFatal(format, FDGL::errorSourceToString(source).c_str(),
                   FDGL::errorTypeToString(type).c_str(),
                   FDGL::errorSeverityToString(level).c_str(),
                   id, msg.data());
        break;

        default:
            qDebug(format, FDGL::errorSourceToString(source).c_str(),
                   FDGL::errorTypeToString(type).c_str(),
                   FDGL::errorSeverityToString(level).c_str(),
                   id, msg.data());
        break;
    }
}

void Renderer::debugCallbackHelper(GLenum source, GLenum type, GLuint id,
                                   GLenum severity, GLsizei length,
                                   const GLchar *message, const void *userParam)
{
    const Renderer *r = reinterpret_cast<const Renderer *>(userParam);
    r->onError(static_cast<FDGL::ErrorSoure>(source),
               static_cast<FDGL::ErrorType>(type), id,
               static_cast<FDGL::ErrorSeverity>(severity),
               std::string(message, static_cast<size_t>(length)));
}
