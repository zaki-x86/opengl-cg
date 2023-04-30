#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

class Vertex
{
public:
    Vertex();
    Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 texCoord);
    Vertex(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f));
    ~Vertex();

    float* positionData() const noexcept;
    float* colorData() const noexcept;
    float* texCoordData() const noexcept;
    const std::vector<float> data() const noexcept;

    void setPosition(glm::vec3 position);
    void setColor(glm::vec3 color);
    void setTexCoord(glm::vec2 texCoord);

    float x() const noexcept { return m_position[0]; }
    float y() const noexcept { return m_position[1]; }
    float z() const noexcept { return m_position[2]; }
    float r() const noexcept { return m_color[0]; }
    float g() const noexcept { return m_color[1]; }
    float b() const noexcept { return m_color[2]; }
    float u() const noexcept { return m_texCoord[0]; }
    float v() const noexcept { return m_texCoord[1]; }

    size_t size() const noexcept;

private:
    std::vector<float> m_position;
    std::vector<float> m_color;
    std::vector<float> m_texCoord;
};



#endif // !_VERTEX_H_