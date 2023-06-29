#include "OpenGLPipeline.h"

VertexArray::VertexArray()
{
    GL_CALL(glGenVertexArrays(1, &m_id));
}

template<typename _Ty>
void VertexArray::linkAttrib(const Buffer<_Ty>& vbo, const VertexArrayInfo& info) const {
    unsigned long _ = info.offset*sizeof(_Ty);

    GL_CALL(glVertexAttribPointer(info.index, info.size, info.type, info.normalized, info.stride, (void*)_));
    
    GL_CALL(glEnableVertexAttribArray(info.index));
    
}

void VertexArray::linkAttribFast(const VertexArrayInfo &info) const
{
    unsigned long _ = info.offset * sizeof(float);

    GL_CALL(glVertexAttribPointer(info.index, info.size, info.type, info.normalized, info.stride, (void*)_));
    
    GL_CALL(glEnableVertexAttribArray(info.index));
}
