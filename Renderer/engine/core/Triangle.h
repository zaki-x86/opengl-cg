#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <initializer_list>

#include "Shader.h"

class Triangle {
public:
    Triangle(float* vertices, const Shader& shader);
    //Triangle(std::vector<glm::vec3> vertices, const Shader& shader);
    //Triangle(std::initializer_list<float> vertices, const Shader& shader);
    ~Triangle();

    void Draw();

private:
    Shader m_shader;
    float m_vertices[9];
    GLuint m_vao;
    GLuint m_vbo;
};


#endif //!_TRIANGLE_H_