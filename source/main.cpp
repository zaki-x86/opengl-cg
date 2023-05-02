#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <cmath>

#include "engine/opengl/OpenGLApp.h"
#include "engine/core/Window.h"
#include "engine/wrapper/glfw-wrapper.h"
#include "engine/core/Vertex.h"
#include "engine/core/Mesh.h"
//#include "engine/core/Shader.h"
//#include "engine/core/Triangle.h"
//#include "engine/core/utils.h"
//#include "engine/core/Texture.h"



int main(void) {
    //assert(restart_gl_log());
    //gl_log("starting GLFW\n%s\n", glfwGetVersionString());

    GLFWConfig config {};
    config.majorVersion = 3;
    config.minorVersion = 3;
    config.profile = GLFW_OPENGL_CORE_PROFILE;
    config.resizable = false;
    config.forwardCompat = true;
    config.errorCallback = NULL;
    config.framebufferSizeCallback = NULL;

    Window<GLFWWrapper, GLFWConfig> window(config, 800, 600, "LearnOpenGL");
    if (!window.initialized()) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    window.makeContextCurrent();

    OpenGLConfig glConfig {};
    glConfig.enableCullFace = false;
    glConfig.depthFunc = GL_LESS;
    glConfig.enableDepthTest = true;
    glConfig.logGLSLInfo = true;
    glConfig.logOpenGLInfo = true;
    
    OpenGLApp app{glConfig};
    app.init();
    app.setViewport(0, 0, 800, 600);

    using Posf = Pos<float>;
    using Colorf = Color<float>;
    
    Mesh triangle({
        Vertf(Posf(0.5f, 0.5f, 0), Colorf(1.0f, 0.0f, 0.0f)),
        Vertf(Posf(0.5f, -0.5f, 0), Colorf(0.0f, 1.0f, 0.0f)),
        Vertf(Posf(-0.5f, -0.5f, 0), Colorf(0.0f, 0.0f, 1.0f))
    });

    

    while(!window.shouldClose()) {
        app.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        app.clear();
        window.pollEvents();
        window.swapBuffers();
    }


    return 0;
}

