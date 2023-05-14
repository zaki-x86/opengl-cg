#ifndef _CUBE_H_
#define _CUBE_H_

#include "GL/glew.h"

#include "Mesh.h"
#include "../opengl/utils.h"
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

static std::vector<Vertf> CUBE_VERTICES_POS_ONLY({
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

static std::vector<Vertf> CUBE_VERTICES_POS_TEX({
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

static std::vector<Vertf> CUBE_VERTICES_POS_NORM({
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

/**
 * TODO Fix issues with copy, move constructors
 * 
 */
class Cube : public Mesh
{
public:
    Cube(CubeType type = CubeType::POS_ONLY);
    ~Cube();

    inline Mesh getMesh() const { return *this; }
    inline VertexArray&& getVAO()  { return std::move(m_VAO); }
    inline Buffer<float> getVBO() const { return m_VBO; }
    inline Shader& getShader() { return m_Shader; }
    inline Texture getTexture() const { return m_Texture; }

    inline void setShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) { 
        m_Shader.setShaders(vertexShaderPath, fragmentShaderPath);
    }

    void setTexture(const std::string& path) { m_Texture.load(path);}

    inline void useShader() { m_Shader.use(); }
    inline void bindTexture() { m_Texture.bind(); }

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



#endif // !CUBE_H_