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
#include <memory>

#include "utils.h"
#include "Shader.h"
#include "Vertex.h"

/**
 * @brief Simple Mesh class
 * 
 * This class is only responsible for managing mesh data: vertices, and optionally indices.
*/

using Vertf = Vertex<float>;

class Mesh {
public:
    Mesh();

    Mesh (const std::vector<Vertf>& vertices);

    Mesh (std::vector<Vertf>&& vertices);
    
    template<typename _VertexIter>
    Mesh (_VertexIter begin, _VertexIter end);

    Mesh(const std::vector<Vertf>& vertices, const std::vector<GLuint>& indices);

    Mesh(std::vector<Vertf>&& vertices, std::vector<GLuint>&& indices);

    template<typename _VertexIter, typename _IndexIter>
    Mesh(_VertexIter begin, _VertexIter end, _IndexIter ibegin, _IndexIter iend);

    Mesh(const Mesh& other);

    Mesh(Mesh&& other);

    ~Mesh();

    Mesh& operator=(const std::vector<Vertf>& vertices);

    Mesh& operator=(std::vector<Vertf>&& vertices);

    Mesh& operator=(const Mesh& other);

    Mesh& operator=(Mesh&& other);

    std::vector<Vertf>& vertices();

    const std::vector<Vertf>& vertices() const;

    void addVertex(const Vertf& vertex);

    void addVertex(Vertf&& vertex);

    void addIndices(const std::vector<GLuint>& indices);

    void addIndices(std::vector<GLuint>&& indices);

private:
    std::vector<Vertf> m_vertices;
    std::vector<GLuint> m_indices;
};
    

#endif // !_MESH_H_
