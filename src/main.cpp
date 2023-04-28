#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <fstream>

#include "Shader.h"

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

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
}

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);


    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    /// `glfwSetFramebufferSizeCallback` sets the callback function for the window resize event
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    
    /// Triangle

    /// Vertices of a triangle, defined in NDC (Normalized Device Coordinates)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    /// VBO (Vertex buffer object)
    uint32_t VBO;
    /// Generate 1 buffer object name
    glGenBuffers(1, &VBO);
    /// Bind the buffer object to the target GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /// Create and initialize a buffer object's data store
    /// GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /// Vertex array object
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    Shader shader;
    if(!shader.CompileVertexShader("shaders/triangle.vert")) {
        std::string info = shader.GetCompileInfo();
        std::cout << "Vertex shader compile error: " << info << std::endl;
    }
    
    if(!shader.CompileFragmentShader("shaders/triangle.frag")) {
        std::string info = shader.GetCompileInfo();
        std::cout << "Fragment shader compile error: " << info << std::endl;
    }
    
    if(!shader.Link()) {
        std::string info = shader.GetLinkInfo();
        std::cout << "Shader link error: " << info << std::endl;
    }
    
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        processInput(window);
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}