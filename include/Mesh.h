#ifndef _MESH_H_
#define _MESH_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <initializer_list>

#include "utils.h"
#include "Shader.h"
#include "Vertex.h"

class Mesh {
public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Shader shader);
    ~Mesh();

    /// Returns the shader used by this mesh.
    Shader shader() const { return m_shader; }

    /// Sets the shader used by this mesh.
    void setShader(const Shader& shader) noexcept { m_shader = shader; }

    /// Returns the vertices of this mesh.
    const Vertex* vertices() const;

    /// Sets the vertices of this mesh.
    void setVertices(const std::vector<Vertex>& vertices) noexcept;

    /// Returns the indices of this mesh.
    const GLuint* indices() const;

    /// Sets the indices of this mesh.
    void setIndices(const std::vector<GLuint>& indices) noexcept;

    /// Returns the number of vertices of this mesh.
    int verticesSize() const;

    /// Returns the number of indices of this mesh.
    int indicesSize() const;

    /// Returns the vertex array object of this mesh.
    GLuint vao() const { return m_vao; }

    /// Returns the vertex buffer object of this mesh.
    GLuint vbo() const { return m_vbo; }

    /// Returns the element buffer object of this mesh.
    GLuint ebo() const { return m_ebo; }

    /// Update the vertex array object, vertex buffer object, and element buffer object of this mesh.
    void update();

    /// Draws this mesh.
    void Draw(GLenum mode = GL_TRIANGLES);

private:
    Shader m_shader;
    std::vector<float> m_bufferData;
    std::vector<GLuint> m_indexData;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};


#endif // !_MESH_H_
