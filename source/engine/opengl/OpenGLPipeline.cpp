#include "OpenGLPipeline.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::createPointers(std::vector<VertexArrayInfo> info) {
    for (auto& i : info) {
        glEnableVertexAttribArray(i.index);
        glVertexAttribPointer(i.index, i.size, i.type, i.normalized, i.stride, reinterpret_cast<void*>(i.offset));
    }
}

void VertexArray::bind() const {
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

unsigned int VertexArray::id() const {
    return m_id;
}
