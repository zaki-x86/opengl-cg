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

#include "engine/core/Cube.hpp"

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

    OpenGLApp app;
    if (!app.initialized()) {
        std::cerr << "Failed to initialize OpenGLApp" << std::endl;
        return -1;
    }


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //Shader shader("/home/zaki/Tutorials/cg-opengl/assets/shaders/cube.vert", "/home/zaki/Tutorials/cg-opengl/assets/shaders/cube.frag");
    //Texture tex("/home/zaki/Tutorials/cg-opengl/assets/images/container.jpg", GL_TEXTURE0);
    Cube cube;
    cube.setShaders("/home/zaki/Tutorials/cg-opengl/assets/shaders/texture/cube.vert", "/home/zaki/Tutorials/cg-opengl/assets/shaders/texture/cube.frag");
    cube.setTexture("/home/zaki/Tutorials/cg-opengl/assets/images/container.jpg");
    //////////////////////////////////////////////////////////

    // Define model, view and projection matrices
    glm::mat4 model = glm::mat4(1.0);
    glm::mat4 view = glm::mat4(1.0);
    glm::mat4 projection = glm::mat4(1.0);

    // Define view matrix
    // Note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Define projection matrix
    // Note that we're using glm::perspective instead of glm::ortho
    // glm::perspective takes in fov in degrees, so we convert it to radians
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        _update_fps_counter(window.getWindow());
        _update_delta_time(&deltaTime, &lastFrame);
        

        // input
        // -----
        processInput(window.getWindow());

        // render
        // ------
        app.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        app.clear();
        cube.bindTexture();

        cube.useShader();

        if (glfwGetKey(window.getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
            model = glm::translate(model, glm::vec3(0.0f, 0.001f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
            model = glm::translate(model, glm::vec3(0.0f, -0.001f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
            model = glm::translate(model, glm::vec3(-0.001f, 0.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
            model = glm::translate(model, glm::vec3(0.001f, 0.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_R) == GLFW_PRESS) {
            model = glm::mat4(1.0);
        }

        // Define rotations 
        if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            model = glm::rotate(model, glm::radians(0.1f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            model = glm::rotate(model, glm::radians(-0.1f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            model = glm::rotate(model, glm::radians(-0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_E) == GLFW_PRESS) {
            model = glm::rotate(model, glm::radians(-0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
        }

        // Define scaling 
        if (glfwGetKey(window.getWindow(), GLFW_KEY_Z) == GLFW_PRESS) {
            model = glm::scale(model, glm::vec3(1.001f, 1.001f, 1.001f));
        }
        else if (glfwGetKey(window.getWindow(), GLFW_KEY_X) == GLFW_PRESS) {
            model = glm::scale(model, glm::vec3(0.999f, 0.999f, 0.999f));
        }

        cube.getShader().setUniform("model", model);
        cube.getShader().setUniform("view", view);
        cube.getShader().setUniform("projection", projection);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //vao.bind();
        //glBindVertexArray(vao.id());
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        cube.draw();
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        window.pollEvents();
    }
    
    return 0;
}


// std::tuple<VertexArray, Shader> createSquareMesh() {

//     static Shader shader("/home/zaki/Tutorials/cg-opengl/build/bin/assets/shaders/triangle.vert", "/home/zaki/Tutorials/cg-opengl/build/bin/assets/shaders/triangle.frag");
//     shader.compile();
//     #ifdef _DEBUG
//     ShaderDebugInfo debugInfo = shader.getDebugInfo();
//     std::cout << "Vertex shader info log: " << debugInfo.VertexShaderCompileInfo << std::endl;
//     std::cout << "Fragment shader info log: " << debugInfo.FragmentShaderCompileInfo << std::endl;
//     std::cout << "Shader program info log: " << debugInfo.LinkInfo << std::endl;
//     #endif

//     static std::vector<Vertf> _v = {
//         Vertf(Posf( 0.5f,  0.5f, 0.0f), Colorf(1.0f, 0.0f, 0.0f)),  // top right
//         Vertf(Posf( 0.5f, -0.5f, 0.0f), Colorf(0.0f, 0.0f, 0.0f)),  // bottom right
//         Vertf(Posf(-0.5f, -0.5f, 0.0f), Colorf(0.0f, 0.0f, 0.0f)),  // bottom left
//         Vertf(Posf(-0.5f,  0.5f, 0.0f), Colorf(0.0f, 0.0f, 0.0f))   // top left 
//     };

//     static Mesh square(_v);
//     square.addIndices({0, 1, 3, 1, 2, 3});

//     static std::vector<float> vertData = square.data();
//     static unsigned int* indices = square.indices();


//     static VertexArray vao;
//     vao.create();
//     vao.bind();

//     static BufferInfo<float> vboInfo{};
//     vboInfo.type = VERTEX_BUFFER;
//     vboInfo.target = GL_ARRAY_BUFFER;
//     vboInfo.data = vertData.data();
//     vboInfo.size = square.vertexByteCount();
//     vboInfo.usage = GL_STATIC_DRAW;
    
//     static Buffer vbo(vboInfo);

//     static BufferInfo<unsigned int> eboInfo{};
//     eboInfo.type = INDEX_BUFFER;
//     eboInfo.target = GL_ELEMENT_ARRAY_BUFFER;
//     eboInfo.data = indices;
//     eboInfo.size = square.indexByteCount();
//     eboInfo.usage = GL_STATIC_DRAW;
    
//     static Buffer ebo(eboInfo);

//     // position pointer info
//     static VertexArrayInfo vaoInfo{};
//     vaoInfo.index = 0;
//     vaoInfo.size = 3;
//     vaoInfo.type = GL_FLOAT;
//     vaoInfo.normalized = GL_FALSE;
//     vaoInfo.stride = 6 * sizeof(float);
//     vaoInfo.offset = 0;

//     // color pointer info
//     static VertexArrayInfo vaoInfo2{};
//     vaoInfo2.index = 1;
//     vaoInfo2.size = 3;
//     vaoInfo2.type = GL_FLOAT;
//     vaoInfo2.normalized = GL_FALSE;
//     vaoInfo2.stride = 6 * sizeof(float);
//     vaoInfo2.offset = 3 * sizeof(float);
//     vao.linkAttribFast(vaoInfo);
//     vao.linkAttribFast(vaoInfo2);
//     vao.unbind();

//     return std::make_tuple(vao, shader);
// }

// std::tuple<Mesh, VertexArray, Buffer, Shader, Texture> createCubeMesh() {
//     Shader shader("/home/zaki/Tutorials/cg-opengl/assets/shaders/cube.vert", "/home/zaki/Tutorials/cg-opengl/assets/shaders/cube.frag");
//     shader.compile();
//     #ifdef _DEBUG
//     ShaderDebugInfo debugInfo = shader.getDebugInfo();
//     std::cout << "Vertex shader info log: " << debugInfo.VertexShaderCompileInfo << std::endl;
//     std::cout << "Fragment shader info log: " << debugInfo.FragmentShaderCompileInfo << std::endl;
//     std::cout << "Shader program info log: " << debugInfo.LinkInfo << std::endl;
//     #endif

//     Mesh Cube({
//         Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 0.0f)),
//         Vertf(Posf( 0.5f, -0.5f, -0.5f),  Tex2D(1.0f, 0.0f)),
//         Vertf(Posf( 0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
//         Vertf(Posf( 0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
//         Vertf(Posf(-0.5f,  0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
//         Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 0.0f)),

//         Vertf(Posf(-0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
//         Vertf(Posf( 0.5f, -0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
//         Vertf(Posf( 0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 1.0f)),
//         Vertf(Posf( 0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 1.0f)),
//         Vertf(Posf(-0.5f,  0.5f,  0.5f),  Tex2D(0.0f, 1.0f)),
//         Vertf(Posf(-0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),

//         Vertf(Posf(-0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
//         Vertf(Posf(-0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
//         Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
//         Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
//         Vertf(Posf(-0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
//         Vertf(Posf(-0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),

//         Vertf(Posf(0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
//         Vertf(Posf(0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
//         Vertf(Posf(0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
//         Vertf(Posf(0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
//         Vertf(Posf(0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
//         Vertf(Posf(0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),

//         Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
//         Vertf(Posf( 0.5f, -0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
//         Vertf(Posf( 0.5f, -0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
//         Vertf(Posf( 0.5f, -0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
//         Vertf(Posf(-0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
//         Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),

//         Vertf(Posf(-0.5f,  0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
//         Vertf(Posf( 0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
//         Vertf(Posf( 0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
//         Vertf(Posf( 0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
//         Vertf(Posf(-0.5f,  0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
//         Vertf(Posf(-0.5f,  0.5f, -0.5f),  Tex2D(0.0f, 1.0f))
//     });

//     std::vector<float> vertData = Cube.data();

//     VertexArray vao;
//     vao.create();
//     vao.bind();
//     GL_LOG("Created VAO with ID: %d\n", vao.id());

//     BufferInfo<float> vboInfo{};
//     vboInfo.type = VERTEX_BUFFER;
//     vboInfo.target = GL_ARRAY_BUFFER;
//     vboInfo.data = vertData.data();
//     vboInfo.size = Cube.vertexByteCount();
//     vboInfo.usage = GL_STATIC_DRAW;
//     Buffer<float> vbo(vboInfo);

//     VertexArrayInfo posInfo{};
//     posInfo.index = 0;
//     posInfo.size = 3;
//     posInfo.type = GL_FLOAT;
//     posInfo.normalized = GL_FALSE;
//     posInfo.stride = 5 * sizeof(float);
//     posInfo.offset = 0;

//     VertexArrayInfo texInfo{};
//     texInfo.index = 1;
//     texInfo.size = 2;
//     texInfo.type = GL_FLOAT;
//     texInfo.normalized = GL_FALSE;
//     texInfo.stride = 5 * sizeof(float);
//     texInfo.offset = 3;

//     vao.linkAttribFast(posInfo);
//     vao.linkAttribFast(texInfo);
//     vao.unbind();

//     Texture tex("/home/zaki/Tutorials/cg-opengl/assets/images/container.jpg", GL_TEXTURE0);

//     return std::make_tuple(Cube, vao, vbo, shader, tex);
// }