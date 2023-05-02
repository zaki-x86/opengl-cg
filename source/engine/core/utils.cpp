#include "utils.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // suppress `unused parameter 'window'` warning
    (void)window;
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // toggle fullscreen mode, `F11` key
    if(glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if(glfwGetWindowMonitor(window) == nullptr) {
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        } else {
            glfwSetWindowMonitor(window, nullptr, 0, 0, windowWidth, windowHeight, mode->refreshRate);
        }
    }
}

/**
 * @brief Gradually cycle from 0 to 1 and back to 0 on a sine wave for a given color
 * 
 * @note This function is to be executed in the main loop
 * 
 * @param colorName the color to cycle
 * @param colorVec the color vector to modify
 */
void gradualColorCycle(RGB colorName, glm::vec3* colorVec) {
    float timeValue = glfwGetTime();
    float colorValue = sin(timeValue) / 2.0f + 0.5f;

    switch (colorName)
    {
    case RGB::RED:
        colorVec->r = colorValue;
        break;
    case RGB::GREEN:
        colorVec->g = colorValue;
        break;
    case RGB::BLUE:
        colorVec->b = colorValue;
        break;
    default:
        break;
    }
}

void glfw_error_callback(int error, const char* description) {
    gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

void _update_fps_counter(GLFWwindow* window) {
    static double previous_seconds = glfwGetTime();
    static int frame_count;
    double current_seconds = glfwGetTime();
    double elapsed_seconds = current_seconds - previous_seconds;

    if (elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        double fps = (double)frame_count / elapsed_seconds;
        char tmp[128];
        sprintf(tmp, "opengl @ fps: %.2f", fps);
        glfwSetWindowTitle(window, tmp);
        frame_count = 0;
    }

    frame_count++;
}

void _glCheckErrors(const char *filename, int line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("OpenGL Error: %s (%d) [%u] %s\n", filename, line, err, glGetErrorString(err));
}