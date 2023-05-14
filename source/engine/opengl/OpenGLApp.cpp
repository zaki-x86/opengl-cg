#include "OpenGLApp.h"

OpenGLApp::OpenGLApp(const OpenGLConfig& config)
    : m_initialized(false), m_enableDepthTest(false), m_enableCullFace(false) 
{
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        m_initialized = false;
    }

    if(config.logOpenGLInfo) {
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("OpenGL version supported: %s\n", glGetString(GL_VERSION));
    }

    if(config.logGLSLInfo) {
        printf("GLSL version supported: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
        printf("Vendor: %s\n", glGetString(GL_VENDOR));
    }

    if(config.enableCullFace) {
        glEnable(GL_CULL_FACE);
        glCullFace(config.cullFace);
        m_enableCullFace = true;
    }

    if(config.enableDepthTest) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(config.depthFunc);
        m_enableDepthTest = true;
    }

    m_initialized = true;
}

OpenGLApp::~OpenGLApp() {
}

bool OpenGLApp::initialized() {
    return m_initialized;
}

void OpenGLApp::setClearColor(float r, float g, float b, float a) {
    GL_CALL(glClearColor(r, g, b, a));
}

void OpenGLApp::enableDepthTest(GLenum func) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(func);
}

void OpenGLApp::disableDepthTest() {
    glDisable(GL_DEPTH_TEST);
}

void OpenGLApp::enableCullFace(GLenum cullFace) {
    glEnable(GL_CULL_FACE);
    glCullFace(cullFace);
}

void OpenGLApp::disableCullFace() {
    glDisable(GL_CULL_FACE);
}

std::string OpenGLApp::getOpenGLVersion() const {
    return std::string((char*)glGetString(GL_VERSION));
}

std::string OpenGLApp::getGLSLVersion() const {
    return std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

std::string OpenGLApp::getVendor() const {
    return std::string((char*)glGetString(GL_VENDOR));
}

std::string OpenGLApp::getRenderer() const {
    return std::string((char*)glGetString(GL_RENDERER));
}

void OpenGLApp::setViewport(int x, int y, int width, int height) {
    GL_CALL(glViewport(x, y, width, height));
}

void OpenGLApp::clear() {
    if(m_enableDepthTest) {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
    else {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    }
}
