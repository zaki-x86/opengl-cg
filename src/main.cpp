#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>

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
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /// `glfwSetFramebufferSizeCallback` sets the callback function for the window resize event
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();    

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwTerminate();
    return 0;
}