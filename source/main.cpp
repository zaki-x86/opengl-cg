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
    // vertex shader
    Shader shader("/home/zaki/Tutorials/cg-opengl/build/bin/assets/shaders/triangle.vert", "/home/zaki/Tutorials/cg-opengl/build/bin/assets/shaders/triangle.frag");
    shader.compile();
    ShaderDebugInfo debugInfo = shader.getDebugInfo();
    std::cout << "Vertex shader info log: " << debugInfo.VertexShaderCompileInfo << std::endl;
    std::cout << "Fragment shader info log: " << debugInfo.FragmentShaderCompileInfo << std::endl;
    std::cout << "Shader program info log: " << debugInfo.LinkInfo << std::endl;
    GL_CHECK_ERRORS();

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
    float* vertices = vertData.data();
    unsigned int* indices = square.indices();

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

    VertexArray vao;
    vao.bind();

    BufferInfo<float> vboInfo{};
    vboInfo.type = VERTEX_BUFFER;
    vboInfo.target = GL_ARRAY_BUFFER;
    vboInfo.data = vertices;
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

    vao.createPointers({vaoInfo, vaoInfo2});
    vao.unbind();


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
        vao.bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        window.pollEvents();
    }
    
    return 0;
}
