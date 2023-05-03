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
using Normf = Normal<float>;

enum class CubeType {
    POS_ONLY,
    POS_COLOR,
    POS_TEX,
    POS_TEX_NORM,
    POS_TEX_NORM_TAN_BITAN,
    POS_NORM
};

std::vector<Vertf> CUBE_VERTICES_POS_ONLY({
    Vertf(Posf(-0.5f, -0.5f, -0.5f)),
    Vertf(Posf( 0.5f, -0.5f, -0.5f)),
    Vertf(Posf( 0.5f,  0.5f, -0.5f)),
    Vertf(Posf( 0.5f,  0.5f, -0.5f)),
    Vertf(Posf(-0.5f,  0.5f, -0.5f)),
    Vertf(Posf(-0.5f, -0.5f, -0.5f)),

    Vertf(Posf(-0.5f, -0.5f,  0.5f)),
    Vertf(Posf( 0.5f, -0.5f,  0.5f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f)),
    Vertf(Posf(-0.5f,  0.5f,  0.5f)),
    Vertf(Posf(-0.5f, -0.5f,  0.5f)),

    Vertf(Posf(-0.5f,  0.5f,  0.5f)),
    Vertf(Posf(-0.5f,  0.5f, -0.5f)),
    Vertf(Posf(-0.5f, -0.5f, -0.5f)),
    Vertf(Posf(-0.5f, -0.5f, -0.5f)),
    Vertf(Posf(-0.5f, -0.5f,  0.5f)),
    Vertf(Posf(-0.5f,  0.5f,  0.5f)),

    Vertf(Posf(0.5f,  0.5f,  0.5f)),
    Vertf(Posf(0.5f,  0.5f, -0.5f)),
    Vertf(Posf(0.5f, -0.5f, -0.5f)),
    Vertf(Posf(0.5f, -0.5f, -0.5f)),
    Vertf(Posf(0.5f, -0.5f,  0.5f)),
    Vertf(Posf(0.5f,  0.5f,  0.5f)),

    Vertf(Posf(-0.5f, -0.5f, -0.5f)),
    Vertf(Posf( 0.5f, -0.5f, -0.5f)),
    Vertf(Posf( 0.5f, -0.5f,  0.5f)),
    Vertf(Posf( 0.5f, -0.5f,  0.5f)),
    Vertf(Posf(-0.5f, -0.5f,  0.5f)),
    Vertf(Posf(-0.5f, -0.5f, -0.5f)),

    Vertf(Posf(-0.5f,  0.5f, -0.5f)),
    Vertf(Posf( 0.5f,  0.5f, -0.5f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f)),
    Vertf(Posf(-0.5f,  0.5f,  0.5f)),
    Vertf(Posf(-0.5f,  0.5f, -0.5f))
});

std::vector<Vertf> CUBE_VERTICES_POS_TEX({
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
});

std::vector<Vertf> CUBE_VERTICES_POS_NORM({
    Vertf(Posf(-0.5f, -0.5f, -0.5f),  Normf(0.0f,  0.0f, -1.0f)),
    Vertf(Posf( 0.5f, -0.5f, -0.5f),  Normf(0.0f,  0.0f, -1.0f)), 
    Vertf(Posf( 0.5f,  0.5f, -0.5f),  Normf(0.0f,  0.0f, -1.0f)), 
    Vertf(Posf( 0.5f,  0.5f, -0.5f),  Normf(0.0f,  0.0f, -1.0f)), 
    Vertf(Posf(-0.5f,  0.5f, -0.5f),  Normf(0.0f,  0.0f, -1.0f)), 
    Vertf(Posf(-0.5f, -0.5f, -0.5f),  Normf(0.0f,  0.0f, -1.0f)), 
    Vertf(Posf(-0.5f, -0.5f,  0.5f),  Normf(0.0f,  0.0f, 1.0f)),
    Vertf(Posf( 0.5f, -0.5f,  0.5f),  Normf(0.0f,  0.0f, 1.0f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f),  Normf(0.0f,  0.0f, 1.0f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f),  Normf(0.0f,  0.0f, 1.0f)),
    Vertf(Posf(-0.5f,  0.5f,  0.5f),  Normf(0.0f,  0.0f, 1.0f)),
    Vertf(Posf(-0.5f, -0.5f,  0.5f),  Normf(0.0f,  0.0f, 1.0f)),
    Vertf(Posf(-0.5f,  0.5f,  0.5f), Normf(-1.0f,  0.0f,  0.0f)),
    Vertf(Posf(-0.5f,  0.5f, -0.5f), Normf(-1.0f,  0.0f,  0.0f)),
    Vertf(Posf(-0.5f, -0.5f, -0.5f), Normf(-1.0f,  0.0f,  0.0f)),
    Vertf(Posf(-0.5f, -0.5f, -0.5f), Normf(-1.0f,  0.0f,  0.0f)),
    Vertf(Posf(-0.5f, -0.5f,  0.5f), Normf(-1.0f,  0.0f,  0.0f)),
    Vertf(Posf(-0.5f,  0.5f,  0.5f), Normf(-1.0f,  0.0f,  0.0f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f),  Normf(1.0f,  0.0f,  0.0f)),
    Vertf(Posf( 0.5f,  0.5f, -0.5f),  Normf(1.0f,  0.0f,  0.0f)),
    Vertf(Posf( 0.5f, -0.5f, -0.5f),  Normf(1.0f,  0.0f,  0.0f)),
    Vertf(Posf( 0.5f, -0.5f, -0.5f),  Normf(1.0f,  0.0f,  0.0f)),
    Vertf(Posf( 0.5f, -0.5f,  0.5f),  Normf(1.0f,  0.0f,  0.0f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f),  Normf(1.0f,  0.0f,  0.0f)),
    Vertf(Posf(-0.5f, -0.5f, -0.5f),  Normf(0.0f, -1.0f,  0.0f)),
    Vertf(Posf( 0.5f, -0.5f, -0.5f),  Normf(0.0f, -1.0f,  0.0f)),
    Vertf(Posf( 0.5f, -0.5f,  0.5f),  Normf(0.0f, -1.0f,  0.0f)),
    Vertf(Posf( 0.5f, -0.5f,  0.5f),  Normf(0.0f, -1.0f,  0.0f)),
    Vertf(Posf(-0.5f, -0.5f,  0.5f),  Normf(0.0f, -1.0f,  0.0f)),
    Vertf(Posf(-0.5f, -0.5f, -0.5f),  Normf(0.0f, -1.0f,  0.0f)),
    Vertf(Posf(-0.5f,  0.5f, -0.5f),  Normf(0.0f,  1.0f,  0.0f)),
    Vertf(Posf( 0.5f,  0.5f, -0.5f),  Normf(0.0f,  1.0f,  0.0f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f),  Normf(0.0f,  1.0f,  0.0f)),
    Vertf(Posf( 0.5f,  0.5f,  0.5f),  Normf(0.0f,  1.0f,  0.0f)),
    Vertf(Posf(-0.5f,  0.5f,  0.5f),  Normf(0.0f,  1.0f,  0.0f)),
    Vertf(Posf(-0.5f,  0.5f, -0.5f),  Normf(0.0f,  1.0f,  0.0f))
});

class Cube : public Mesh
{
public:
    Cube(CubeType type = CubeType::POS_ONLY);
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
    VertexArrayInfo m_normInfo;
    VertexArray m_VAO;
    BufferInfo<float> m_VBOInfo;
    Buffer<float> m_VBO;
    Shader m_Shader;
    Texture m_Texture;

    void _posOnlyCube();
    void _posTexCube();
    void _posNormCube();
};

Cube::Cube(CubeType type) : 
    Mesh(),
    m_VAO(), 
    m_VBOInfo(),
    m_Shader(),
    m_Texture()
{
    // set vertex data
    if(type == CubeType::POS_ONLY) {
        _posOnlyCube();
    }

    else if(type == CubeType::POS_TEX) {
        _posTexCube();
    }

    else if(type == CubeType::POS_NORM) {
        _posNormCube();
    }
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

void Cube::_posOnlyCube()
{
    setVertices(CUBE_VERTICES_POS_ONLY);
    m_posInfo = VertexArrayInfo{};

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

    m_VAO.linkAttribFast(m_posInfo);
    m_VAO.unbind();
}

void Cube::_posTexCube()
{
    setVertices(CUBE_VERTICES_POS_TEX);
    m_posInfo = VertexArrayInfo{};
    m_texInfo = VertexArrayInfo{};

    // log vertex data
    GL_LOG("Vertex data: \n");
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

void Cube::_posNormCube()
{
    setVertices(CUBE_VERTICES_POS_NORM);
    m_posInfo = VertexArrayInfo{};
    m_normInfo = VertexArrayInfo{};

    // log vertex data
    GL_LOG("Vertex data: \n");
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
    m_posInfo.stride = 6 * sizeof(float);
    m_posInfo.offset = 0;

    m_normInfo.index = 1;
    m_normInfo.size = 3;
    m_normInfo.type = GL_FLOAT;
    m_normInfo.normalized = GL_FALSE;
    m_normInfo.stride = 6 * sizeof(float);
    m_normInfo.offset = 3;

    m_VAO.linkAttribFast(m_posInfo);
    m_VAO.linkAttribFast(m_normInfo);
    m_VAO.unbind();
}

#endif // !CUBE_H_