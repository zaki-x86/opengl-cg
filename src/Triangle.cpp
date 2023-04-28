#include "Triangle.h"


Triangle::Triangle(float* vertices, const Shader& shader)
    : m_shader(shader)
{
    for (int i = 0; i < 9; i++)
        m_vertices[i] = vertices[i];

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER,
                 9 * sizeof(float),
                 vertices,
                 GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);
}

Triangle::~Triangle()
{
    //glDeleteVertexArrays(1, &m_vao);
    //glDeleteBuffers(1, &m_vbo);
}

void Triangle::Draw()
{
    m_shader.Use();
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}