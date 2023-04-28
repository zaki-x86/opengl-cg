#ifndef _GENERICSHAPE_H_
#define _GENERICSHAPE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <initializer_list>

#include "Shader.h"

class GenericShape {
public:
    GenericShape(std::vector<float> vertices, std::vector<int> indices, const Shader& shader);
    ~GenericShape();

    void Draw(GLenum mode = GL_TRIANGLES);

private:
    Shader m_shader;
    std::vector<float> m_vertices;
    std::vector<int> m_indices;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};


#endif // !_GENERICSHAPE_H_
