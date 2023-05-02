#ifndef _OPENGLAPP_H_
#define _OPENGLAPP_H_

#include <GL/glew.h>

#include <iostream>

#include "../core/Window.h"


/**
 * @brief Simple OpenGL application class
 * 
 * This class is responsible for managing the application's main loop.
 * 
 * It is also responsible for initializing and terminating GLFW and GLEW.
 * 
 * It is also responsible for creating the window.
 * 
 * It is also responsible for setting up the OpenGL context.
 * 
 * It is also responsible for setting up the OpenGL viewport.
 * 
 * It is also responsible for setting up the OpenGL clear color.
 * 
 * It is also responsible for setting up the OpenGL depth test.
 
 */

struct OpenGLConfig {
    bool enableDepthTest;
    GLenum depthFunc;
    bool enableCullFace;
    GLenum cullFace;
    bool logOpenGLInfo;
    bool logGLSLInfo;
};

class OpenGLApp {
public:
    OpenGLApp(const OpenGLConfig& config = { true, GL_LESS, false, GL_BACK, true, true });

    OpenGLApp(const OpenGLApp& other) = delete;

    OpenGLApp(OpenGLApp&& other) = delete;

    ~OpenGLApp();

    OpenGLApp& operator=(const OpenGLApp& other) = delete;

    OpenGLApp& operator=(OpenGLApp&& other) = delete;

    bool initialized();

    void setClearColor(float r, float g, float b, float a);

    void enableDepthTest(GLenum func = GL_LESS);

    void disableDepthTest();

    void enableCullFace(GLenum cullFace);

    void disableCullFace();

    std::string getOpenGLVersion() const;

    std::string getGLSLVersion() const;

    std::string getVendor() const;

    std::string getRenderer() const;

    void clear();

    void setViewport(int x = 0, int y = 0, int width = 800, int height = 600);

private:
    bool m_initialized;
    bool m_enableDepthTest;
    bool m_enableCullFace;
};

#endif // !