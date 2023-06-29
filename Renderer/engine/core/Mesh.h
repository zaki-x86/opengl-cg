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

#include "../opengl/utils.h"
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
    using vertex_type = Vertex<float>;
    using vertex_reference = vertex_type&;
    using vertex_const_reference = const vertex_type&;
    using vertex_pointer = vertex_type*;
    using const_pointer = const vertex_type*;
    using index_type = unsigned int;
    using size_type = unsigned int;

    Mesh();

    Mesh (const std::vector<Vertf>& vertices);

    Mesh (std::vector<Vertf>&& vertices);
    
    template<typename _VertexIter>
    Mesh (_VertexIter begin, _VertexIter end);

    Mesh(const std::vector<Vertf>& vertices, const std::vector<unsigned int>& indices);

    Mesh(std::vector<Vertf>&& vertices, std::vector<unsigned int>&& indices);

    template<typename _VertexIter, typename _IndexIter>
    Mesh(_VertexIter begin, _VertexIter end, _IndexIter ibegin, _IndexIter iend);

    Mesh(const Mesh& other);

    Mesh(Mesh&& other);

    ~Mesh();

    Mesh& operator=(const std::vector<Vertf>& vertices);

    Mesh& operator=(std::vector<Vertf>&& vertices);

    Mesh& operator=(const Mesh& other);

    Mesh& operator=(Mesh&& other);

    Vertf* vertices();

    const Vertf* vertices() const;

    unsigned int* indices();

    const unsigned int* indices() const;

    void setVertices(const std::vector<Vertf>& vertices);

    void setVertices(std::vector<Vertf>&& vertices);

    void addVertex(const Vertf& vertex);

    void addVertex(Vertf&& vertex);

    void addIndices(const std::vector<unsigned int>& indices);

    void addIndices(std::vector<unsigned int>&& indices);

    unsigned int vertexCount() const;

    unsigned int indexCount() const;

    unsigned int perVertexCount() const;

    unsigned int size() const;

    unsigned long vertexByteCount() const;

    unsigned long indexByteCount() const;

    std::vector<vertex_type::value_type> data();

private:
    std::vector<Vertf> m_vertices;
    std::vector<unsigned int> m_indices;
};
    

#endif // !_MESH_H_
