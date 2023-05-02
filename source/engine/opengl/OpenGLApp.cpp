#include "OpenGLApp.h"

OpenGLApp::OpenGLApp(const OpenGLConfig& config) {
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
    }

    if(config.enableDepthTest) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(config.depthFunc);
    }

}

OpenGLApp::~OpenGLApp() {
}

bool OpenGLApp::init() {
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    // get version infoWindowHandler

    
    
    return true;
}

void OpenGLApp::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
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
    glViewport(x, y, width, height);
}

void OpenGLApp::clear() {
    if(m_enableDepthTest)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else
        glClear(GL_COLOR_BUFFER_BIT);
}
