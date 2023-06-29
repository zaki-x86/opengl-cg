#include "glfw-wrapper.h"
#include <GLFW/glfw3.h>


GLFWWrapper::GLFWWrapper(const GLFWConfig& config, int width, int height, const std::string& title) : m_initialized(false), m_title(title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, config.profile);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, config.forwardCompat);
    if(config.errorCallback)
        glfwSetErrorCallback(config.errorCallback);
    if(config.framebufferSizeCallback)
        glfwSetFramebufferSizeCallback(m_window, config.framebufferSizeCallback);

    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_window) {
        std::cerr << "Failed to create GLFW m_window" << std::endl;
    }
    m_initialized = true;
}

bool GLFWWrapper::initialized() const {
    return m_initialized;
}

void GLFWWrapper::destroy() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool GLFWWrapper::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void GLFWWrapper::setShouldClose(bool value) {
    glfwSetWindowShouldClose(m_window, value);
}

void GLFWWrapper::swapBuffers() {
    glfwSwapBuffers(m_window);
}

void GLFWWrapper::pollEvents() {
    glfwPollEvents();
}

std::pair<int, int> GLFWWrapper::getSize() const {
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    return std::make_pair(width, height);
}

void GLFWWrapper::setSize(int width, int height) {
    glfwSetWindowSize(m_window, width, height);
}

std::pair<int, int> GLFWWrapper::getFramebufferSize() const {
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    return std::make_pair(width, height);
}

GLFWwindow* GLFWWrapper::getWindow() const {
    return m_window;
}


void GLFWWrapper::setTitle(const std::string& title) {
    m_title = title;
    glfwSetWindowTitle(m_window, title.c_str());
}

std::string GLFWWrapper::getTitle() const {
    return m_title;
}

void GLFWWrapper::makeContextCurrent() {
    glfwMakeContextCurrent(m_window);
}