#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <fstream>
#include <cmath>

#include "Shader.h"
#include "Triangle.h"
#include "Mesh.h"
#include "utils.h"

GLuint SetupTriangle();
void DrawTriangle(Shader, GLuint vao);

int main(void) {
    assert(restart_gl_log());

    gl_log("starting GLFW\n%s\n", glfwGetVersionString());

    // register the error call-back function
    glfwSetErrorCallback(glfw_error_callback);

    if(!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /// Anti-aliasing
    /// This can get too slow if you have a large number of objects 
    //glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(
    600, 400, "Extended GL Init", NULL, NULL);

    if(!window) {
        std::cout << "Failed to create a window" << std::endl;
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


    #if _DEBUG
        Shader shader("shaders/01/triangle.vert", "shaders/01/triangle.frag");
        shader.Compile();
        ShaderDebugInfo& debugInfo = shader.GetDebugInfo();
        std::cout << "Vertex shader info log: " << debugInfo.VertexShaderCompileInfo << std::endl;
        std::cout << "Fragment shader info log: " << debugInfo.FragmentShaderCompileInfo << std::endl;
        std::cout << "Shader program info log: " << debugInfo.LinkInfo << std::endl;
    #else
        Shader shader("shaders/triangle.vert", "shaders/triangle.frag");
        shader.Compile();
    #endif


    while(!glfwWindowShouldClose(window))
    {
        _update_fps_counter(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // update the uniform color
        //gradualColorCycle(RGB::GREEN, &_color);
        //int vertexColorLocation = glGetUniformLocation(shader.GetProgramID(), "ourColor");
        //glUniform4f(vertexColorLocation, _color.x, _color.y, _color.z, 1.0f);
        
        processInput(window);
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

GLuint SetupTriangle() {
    float _vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f, 1.0f, 0.0, 0.0f, 0.0f, 0.0f,// bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0, 0.0f, 0.0f, 0.0f,// bottom left
         0.0f,  0.5f, 0.0f, 0.0f, 0.0, 1.0f, 0.0f, 0.0f// top 
    };
    GLuint _indices[] = { 0, 1, 2 };

    GLuint VBO, VAO;
    GLuint EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), _vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), _indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0); //Unbind the VAO

    return VAO;
}

void DrawTriangle(Shader shader, GLuint vao) {
    shader.Use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}