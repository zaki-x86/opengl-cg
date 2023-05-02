#include "Mesh.h"

Mesh::Mesh() : m_vertices(), m_indices() {}

Mesh::Mesh (const std::vector<Vertf>& vertices) : m_vertices(vertices), m_indices() {}

Mesh::Mesh (std::vector<Vertf>&& vertices) : m_vertices(std::move(vertices)), m_indices() {}

template<typename _VertexIter>
Mesh::Mesh (_VertexIter begin, _VertexIter end) : m_vertices(begin, end), m_indices() {}

Mesh::Mesh(const std::vector<Vertf>& vertices, const std::vector<GLuint>& indices) : m_vertices(vertices), m_indices(indices) {}

Mesh::Mesh(std::vector<Vertf>&& vertices, std::vector<GLuint>&& indices) : m_vertices(std::move(vertices)), m_indices(std::move(indices)) {}

template<typename _VertexIter, typename _IndexIter>
Mesh::Mesh(_VertexIter begin, _VertexIter end, _IndexIter ibegin, _IndexIter iend) : m_vertices(begin, end), m_indices(ibegin, iend) {}

Mesh::Mesh(const Mesh& other) : m_vertices(other.m_vertices), m_indices(other.m_indices) {}

Mesh::Mesh(Mesh&& other) : m_vertices(std::move(other.m_vertices)), m_indices(std::move(other.m_indices)) {}

Mesh::~Mesh() = default;

Mesh& Mesh::operator=(const std::vector<Vertf>& vertices) {
    m_vertices = vertices;
    return *this;
}

Mesh& Mesh::operator=(std::vector<Vertf>&& vertices) {
    m_vertices = std::move(vertices);
    return *this;
}

Mesh& Mesh::operator=(const Mesh& other) {
    m_vertices = other.m_vertices;
    m_indices = other.m_indices;
    return *this;
}

Mesh& Mesh::operator=(Mesh&& other) {
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
    return *this;
}

std::vector<Vertf>& Mesh::vertices() {
    return m_vertices;
}

const std::vector<Vertf>& Mesh::vertices() const {
    return m_vertices;
}

void Mesh::addVertex(const Vertf& vertex) {
    m_vertices.push_back(vertex);
}

void Mesh::addVertex(Vertf&& vertex) {
    m_vertices.push_back(std::move(vertex));
}

void Mesh::addIndices(const std::vector<GLuint>& indices) {
    m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}

void Mesh::addIndices(std::vector<GLuint>&& indices) {
    m_indices.insert(m_indices.end(), std::make_move_iterator(indices.begin()), std::make_move_iterator(indices.end()));
}