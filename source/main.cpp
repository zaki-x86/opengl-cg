#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "engine/wrapper/glfw-wrapper.h"
#include "engine/opengl/OpenGLApp.h"
#include "engine/opengl/OpenGLPipeline.h"
#include "engine/core/utils.h"
#include "engine/core/Window.h"
#include "engine/core/Shader.h"
#include "engine/core/Texture.h"
#include "engine/core/Vertex.h"
#include "engine/core/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/core/Cube.hpp"
#include "engine/core/Camera.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    glfw_config.majorVersion = 3;
    glfw_config.minorVersion = 3;
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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    OpenGLApp app;
    if (!app.initialized()) {
        std::cerr << "Failed to initialize OpenGLApp" << std::endl;
        return -1;
    }


    // render loop
    // -----------
    while (!window.shouldClose())
    {
        window.pollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        _update_fps_counter(window.getWindow());
        _update_delta_time(&deltaTime, &lastFrame);

        // render
        // ------
        app.clear();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swapBuffers();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
