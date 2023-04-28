#include "GenericShape.h"

GenericShape::GenericShape(std::vector<float> vertices, std::vector<int> indices, const Shader& shader)
: m_shader(shader)
{
    m_vertices = vertices;
    m_indices = indices;

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(float),
                 &m_vertices[0],
                 GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(int),
                 &m_indices[0],
                 GL_STATIC_DRAW);
}

GenericShape::~GenericShape()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void GenericShape::Draw(GLenum mode)
{
    m_shader.Use();
    glBindVertexArray(m_vao);
    glDrawElements(mode, m_indices.size(), GL_UNSIGNED_INT, 0);
}