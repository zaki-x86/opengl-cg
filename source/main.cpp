#include <iostream>

// Engine Window Wrapper
#include "engine/wrapper/glfw-wrapper.h"

// OpenGL
#include "engine/opengl/OpenGLApp.h"
#include "engine/opengl/OpenGLPipeline.h"

// Engine Gui
#include "engine/Gui/gui.h"

// Engine Core
#include "engine/opengl/utils.h"
#include "engine/core/Window.h"
#include "engine/core/Shader.h"
#include "engine/core/Texture.h"
#include "engine/core/Vertex.h"
#include "engine/core/Mesh.h"
#include "engine/core/Cube.hpp"
#include "engine/core/Camera.hpp"

// tests
#include "apps/TestClearColor.h"
#include "apps/TestTexture2D.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 990;

using Vertf = Vertex<float>;
using Posf  = Pos<float>;
using Colorf = Color<float>;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    assert(restart_gl_log());

    GLFWConfig glfw_config{};
    glfw_config.majorVersion = 4;
    glfw_config.minorVersion = 6;
    glfw_config.profile = GLFW_OPENGL_CORE_PROFILE;
    glfw_config.resizable = false;
    glfw_config.forwardCompat = false;
    glfw_config.errorCallback = glfw_error_callback;
    glfw_config.framebufferSizeCallback = NULL;

    Window<GLFWWrapper, GLFWConfig> window(glfw_config, SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    if (!window.initialized()) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    window.makeContextCurrent();
    glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);

    glfwSwapInterval(1); // Enable vsync

    OpenGLApp app;
    if (!app.initialized()) {
        std::cerr << "Failed to initialize OpenGLApp" << std::endl;
        return -1;
    }

    bool show_gui = true;
    EngineGui gui(window.getWindow());

    test::TestApp* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->registerTest<test::TestClearColor>("Clear Color");
    testMenu->registerTest<test::TestTexture2D>("Container Cube");
    

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        _update_fps_counter(window.getWindow());
        _update_delta_time(&deltaTime, &lastFrame);

        window.pollEvents();
        app.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        app.clear();
        
        // ---- Begin Gui Render
        gui.render();

        // render
        // ------

        // -- Begin Main UI
        // ----------------
        if(gui.beginMainUI(&show_gui)) {

            if (currentTest) {
                currentTest->onUpdate(deltaTime);
                currentTest->onRender();
                
                if(currentTest != testMenu && ImGui::Button("Back <")) {
                    delete currentTest;
                    currentTest = testMenu;
                }

                currentTest->onGuiRender();
            }

            gui.endMainUI();
        }


        // ---- End Gui Render
        gui.renderEnd();
        
        window.swapBuffers();
    }

    return 0;
}
