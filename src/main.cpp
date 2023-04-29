#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <fstream>
#include <cmath>

#include "Shader.h"
#include "Triangle.h"
#include "GenericShape.h"

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
    

    /// Vertices of a triangle, defined in NDC (Normalized Device Coordinates)
    /// supress unused variable warning for `vertices`
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f // tip of second triangle
    };


    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    #if _DEBUG
        Shader shader("shaders/triangle.vert", "shaders/triangle.frag");
        shader.Compile();
        ShaderDebugInfo& debugInfo = shader.GetDebugInfo();
        std::cout << "Vertex shader info log: " << debugInfo.VertexShaderCompileInfo << std::endl;
        std::cout << "Fragment shader info log: " << debugInfo.FragmentShaderCompileInfo << std::endl;
        std::cout << "Shader program info log: " << debugInfo.LinkInfo << std::endl;
    #else
        Shader shader("shaders/triangle.vert", "shaders/triangle.frag");
        shader.Compile();
    #endif

    std::vector<float> vertices_vec(vertices, vertices + sizeof(vertices) / sizeof(float));
    std::vector<int> indices_vec(indices, indices + sizeof(indices) / sizeof(float));
    GenericShape shape(vertices_vec, indices_vec, shader);

    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //tr.Draw();
        
        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader.GetProgramID(), "ourColor");
        glUniform4f(vertexColorLocation, 0.5f, greenValue, 1.0f, 0.0f);
        
        shape.Draw();

        processInput(window);
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}