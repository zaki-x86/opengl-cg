#ifndef _CUBE_H_
#define _CUBE_H_

#include "GL/glew.h"

#include "Mesh.h"
#include "utils.h"
#include "Texture.h"
#include "Vertex.h"
#include "Shader.h"

#include "../opengl/OpenGLPipeline.h"

#include <vector>

using Posf = Pos<float>;
using Vertf = Vertex<float>;

class Cube : public Mesh
{
public:
    Cube();
    ~Cube();

    Mesh getMesh() const { return *this; }
    VertexArray getVAO() const { return m_VAO; }
    Buffer<float> getVBO() const { return m_VBO; }
    Shader& getShader() { return m_Shader; }
    Texture getTexture() const { return m_Texture; }

    void setShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) { 
        m_Shader.setShaders(vertexShaderPath, fragmentShaderPath);
        m_Shader.compile();
        #ifdef _DEBUG
        ShaderDebugInfo debugInfo = m_Shader.getDebugInfo();
        std::cout << "Vertex shader info log: " << debugInfo.VertexShaderCompileInfo << std::endl;
        std::cout << "Fragment shader info log: " << debugInfo.FragmentShaderCompileInfo << std::endl;
        std::cout << "Shader program info log: " << debugInfo.LinkInfo << std::endl;
        #endif
    }

    void setTexture(const std::string& path) { m_Texture.load(path);}

    void useShader() { m_Shader.use(); }
    void bindTexture() { m_Texture.bind(); }

    void draw() const;

private:
    VertexArrayInfo m_posInfo;
    VertexArrayInfo m_texInfo;
    VertexArray m_VAO;
    BufferInfo<float> m_VBOInfo;
    Buffer<float> m_VBO;
    Shader m_Shader;
    Texture m_Texture;
};

Cube::Cube()
    : Mesh(std::vector<Vertf>({
        Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 0.0f)),
        Vertf(Posf( 0.5f, -0.5f, -0.5f),  Tex2D(1.0f, 0.0f)),
        Vertf(Posf( 0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
        Vertf(Posf( 0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
        Vertf(Posf(-0.5f,  0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
        Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 0.0f)),

        Vertf(Posf(-0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
        Vertf(Posf( 0.5f, -0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
        Vertf(Posf( 0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 1.0f)),
        Vertf(Posf( 0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 1.0f)),
        Vertf(Posf(-0.5f,  0.5f,  0.5f),  Tex2D(0.0f, 1.0f)),
        Vertf(Posf(-0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),

        Vertf(Posf(-0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
        Vertf(Posf(-0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
        Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
        Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
        Vertf(Posf(-0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
        Vertf(Posf(-0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),

        Vertf(Posf(0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
        Vertf(Posf(0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
        Vertf(Posf(0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
        Vertf(Posf(0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
        Vertf(Posf(0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
        Vertf(Posf(0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),

        Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
        Vertf(Posf( 0.5f, -0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
        Vertf(Posf( 0.5f, -0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
        Vertf(Posf( 0.5f, -0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
        Vertf(Posf(-0.5f, -0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
        Vertf(Posf(-0.5f, -0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),

        Vertf(Posf(-0.5f,  0.5f, -0.5f),  Tex2D(0.0f, 1.0f)),
        Vertf(Posf( 0.5f,  0.5f, -0.5f),  Tex2D(1.0f, 1.0f)),
        Vertf(Posf( 0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
        Vertf(Posf( 0.5f,  0.5f,  0.5f),  Tex2D(1.0f, 0.0f)),
        Vertf(Posf(-0.5f,  0.5f,  0.5f),  Tex2D(0.0f, 0.0f)),
        Vertf(Posf(-0.5f,  0.5f, -0.5f),  Tex2D(0.0f, 1.0f))
    })), 
    m_posInfo(), m_texInfo(), m_VAO(), m_VBOInfo(),
    m_Shader(),
    m_Texture()
{
    // log vertex data
    GL_LOG( "Vertex data: \n");
    for (size_t i = 0; i < vertexByteCount() / sizeof(float); i++)
    {
        GL_LOG("%f ", data().data()[i]);
        if ((i + 1) % 5 == 0)
            GL_LOG("\n");
    }
    GL_LOG("\n");

    m_VAO.create();
    m_VAO.bind();
    GL_LOG("Created VAO with ID: %d\n", m_VAO.id());

    m_VBOInfo.type = VERTEX_BUFFER;
    m_VBOInfo.target = GL_ARRAY_BUFFER;
    m_VBOInfo.data = data();
    m_VBOInfo.size = vertexByteCount();
    m_VBOInfo.usage = GL_STATIC_DRAW;
    m_VBO.setBuffer(m_VBOInfo);

    m_posInfo.index = 0;
    m_posInfo.size = 3;
    m_posInfo.type = GL_FLOAT;
    m_posInfo.normalized = GL_FALSE;
    m_posInfo.stride = 5 * sizeof(float);
    m_posInfo.offset = 0;

    m_texInfo.index = 1;
    m_texInfo.size = 2;
    m_texInfo.type = GL_FLOAT;
    m_texInfo.normalized = GL_FALSE;
    m_texInfo.stride = 5 * sizeof(float);
    m_texInfo.offset = 3;

    m_VAO.linkAttribFast(m_posInfo);
    m_VAO.linkAttribFast(m_texInfo);
    m_VAO.unbind();
}

Cube::~Cube()
{
}

void Cube::draw() const
{
    m_VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_VAO.unbind();
}

#endif // !CUBE_H_