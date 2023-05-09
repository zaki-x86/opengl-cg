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

void processInput2(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using Vertf = Vertex<float>;
using Posf  = Pos<float>;
using Colorf = Color<float>;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


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

    OpenGLApp app;
    if (!app.initialized()) {
        std::cerr << "Failed to initialize OpenGLApp" << std::endl;
        return -1;
    }

    // Handling mouse events
    glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
    glfwSetScrollCallback(window.getWindow(), scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    Cube cube(CubeType::POS_NORM);
    Cube lightCube(CubeType::POS_NORM); // light source

    cube.setShaders("/home/zaki/Tutorials/cg-opengl/assets/shaders/lights/cube.vs", "/home/zaki/Tutorials/cg-opengl/assets/shaders/lights/cube.fs");

    lightCube.setShaders("/home/zaki/Tutorials/cg-opengl/assets/shaders/lights/lightCube.vs", "/home/zaki/Tutorials/cg-opengl/assets/shaders/lights/lightCube.fs");

    // Define light position
    glm::vec3 lightPos(1.0f, 0.5f, 0.31f);

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        _update_fps_counter(window.getWindow());
        _update_delta_time(&deltaTime, &lastFrame);

        // input
        // -----
        processInput2(window.getWindow());

        // render
        // ------
        app.clear();

        cube.useShader();
        cube.getShader().setUniform("objectColor", 1.0f, 0.5f, 0.31f);
        cube.getShader().setUniform("lightColor", 1.0f, 1.0f, 1.0f);
        cube.getShader().setUniform("lightPos", lightPos);
        cube.getShader().setUniform("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 model = glm::mat4(1.0);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        cube.getShader().setUniform("model", model);
        cube.getShader().setUniform("view", view);
        cube.getShader().setUniform("projection", projection);
        cube.draw();

        // Define scaling 
        if (glfwGetKey(window.getWindow(), GLFW_KEY_Z) == GLFW_PRESS) {
            model = glm::scale(model, glm::vec3(1.001f, 1.001f, 1.001f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_X) == GLFW_PRESS) {
            model = glm::scale(model, glm::vec3(0.999f, 0.999f, 0.999f));
        }

        // position the light cube at (1.0f, 0.5f, 0.31f)
        lightCube.useShader();
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightCube.getShader().setUniform("model", model);
        lightCube.getShader().setUniform("view", view);
        lightCube.getShader().setUniform("projection", projection);
        lightCube.getShader().setUniform("lightPos", lightPos);
        lightCube.draw();
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        window.pollEvents();
    }
    
    return 0;
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    (void)window;
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    (void)window;
    (void)xoffset;
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput2(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
