#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

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


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
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

    OpenGLApp app;
    if (!app.initialized()) {
        std::cerr << "Failed to initialize OpenGLApp" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    Shader shader("/home/zaki/Tutorials/cg-opengl/build/bin/assets/shaders/triangle.vert", "/home/zaki/Tutorials/cg-opengl/build/bin/assets/shaders/triangle.frag");
    shader.compile();
    #ifdef _DEBUG
    ShaderDebugInfo debugInfo = shader.getDebugInfo();
    std::cout << "Vertex shader info log: " << debugInfo.VertexShaderCompileInfo << std::endl;
    std::cout << "Fragment shader info log: " << debugInfo.FragmentShaderCompileInfo << std::endl;
    std::cout << "Shader program info log: " << debugInfo.LinkInfo << std::endl;
    #endif

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    using Vertf = Vertex<float>;
    using Posf  = Pos<float>;
    using Colorf = Color<float>;
    
    std::vector<Vertf> _v = {
        Vertf(Posf( 0.5f,  0.5f, 0.0f), Colorf(1.0f, 0.0f, 0.0f)),  // top right
        Vertf(Posf( 0.5f, -0.5f, 0.0f), Colorf(0.0f, 0.0f, 0.0f)),  // bottom right
        Vertf(Posf(-0.5f, -0.5f, 0.0f), Colorf(0.0f, 0.0f, 0.0f)),  // bottom left
        Vertf(Posf(-0.5f,  0.5f, 0.0f), Colorf(0.0f, 0.0f, 0.0f))   // top left 
    };

    Mesh square(_v);
    square.addIndices({0, 1, 3, 1, 2, 3});
    
    std::vector<float> vertData = square.data();
    unsigned int* indices = square.indices();


    VertexArray vao;
    vao.bind();

    BufferInfo<float> vboInfo{};
    vboInfo.type = VERTEX_BUFFER;
    vboInfo.target = GL_ARRAY_BUFFER;
    vboInfo.data = vertData.data();
    vboInfo.size = square.vertexByteCount();
    vboInfo.usage = GL_STATIC_DRAW;
    
    Buffer vbo(vboInfo);

    BufferInfo<unsigned int> eboInfo{};
    eboInfo.type = INDEX_BUFFER;
    eboInfo.target = GL_ELEMENT_ARRAY_BUFFER;
    eboInfo.data = indices;
    eboInfo.size = square.indexByteCount();
    eboInfo.usage = GL_STATIC_DRAW;
    
    Buffer ebo(eboInfo);

    // position pointer info
    VertexArrayInfo vaoInfo{};
    vaoInfo.index = 0;
    vaoInfo.size = 3;
    vaoInfo.type = GL_FLOAT;
    vaoInfo.normalized = GL_FALSE;
    vaoInfo.stride = 6 * sizeof(float);
    vaoInfo.offset = 0;

    // color pointer info
    VertexArrayInfo vaoInfo2{};
    vaoInfo2.index = 1;
    vaoInfo2.size = 3;
    vaoInfo2.type = GL_FLOAT;
    vaoInfo2.normalized = GL_FALSE;
    vaoInfo2.stride = 6 * sizeof(float);
    vaoInfo2.offset = 3 * sizeof(float);
    vao.createPointers({vaoInfo, vaoInfo2});
    vao.unbind();

    // Transformation
    glm::mat4 upTransform = glm::mat4(1.0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        // input
        // -----
        processInput(window.getWindow());

        // render
        // ------
        app.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        app.clear();

        // draw our first triangle
        shader.use();
        vao.bind();

        if (glfwGetKey(window.getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
            upTransform = glm::translate(upTransform, glm::vec3(0.0f, 0.001f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
            upTransform = glm::translate(upTransform, glm::vec3(0.0f, -0.001f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
            upTransform = glm::translate(upTransform, glm::vec3(-0.001f, 0.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
            upTransform = glm::translate(upTransform, glm::vec3(0.001f, 0.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_R) == GLFW_PRESS) {
            upTransform = glm::mat4(1.0);
        }

        // Define rotations 
        if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            upTransform = glm::rotate(upTransform, glm::radians(0.1f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            upTransform = glm::rotate(upTransform, glm::radians(-0.1f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            upTransform = glm::rotate(upTransform, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            upTransform = glm::rotate(upTransform, glm::radians(-0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            upTransform = glm::rotate(upTransform, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_E) == GLFW_PRESS) {
            upTransform = glm::rotate(upTransform, glm::radians(-0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
        }

        // Define scaling 
        if (glfwGetKey(window.getWindow(), GLFW_KEY_Z) == GLFW_PRESS) {
            upTransform = glm::scale(upTransform, glm::vec3(1.001f, 1.001f, 1.001f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_X) == GLFW_PRESS) {
            upTransform = glm::scale(upTransform, glm::vec3(0.999f, 0.999f, 0.999f));
        }
        
        shader.setUniform("transform", upTransform);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        window.pollEvents();
    }
    
    return 0;
}
