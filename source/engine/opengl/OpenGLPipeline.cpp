#include "OpenGLPipeline.h"

void VertexArray::create() {
    glGenVertexArrays(1, &m_id);
    
}

template<typename _Ty>
void VertexArray::linkAttrib(const Buffer<_Ty>& vbo, const VertexArrayInfo& info) const {
    unsigned long _ = info.offset*sizeof(_Ty);

    glVertexAttribPointer(info.index, info.size, info.type, info.normalized, info.stride, (void*)_);
    
    glEnableVertexAttribArray(info.index);
    
}

void VertexArray::linkAttribFast(const VertexArrayInfo& info) const {
    unsigned long _ = info.offset * sizeof(float);

    glVertexAttribPointer(info.index, info.size, info.type, info.normalized, info.stride, (void*)_);
    
    glEnableVertexAttribArray(info.index);
    
}
