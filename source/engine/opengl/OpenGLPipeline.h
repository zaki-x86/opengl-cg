#ifndef _OPENGL_PIPELINE_H_
#define _OPENGL_PIPELINE_H_

#include <GL/glew.h>
#include <vector>
#include "../core/utils.h"

enum BufferType
{
    VERTEX_BUFFER,
    INDEX_BUFFER,
    UNIFORM_BUFFER,
    SHADER_STORAGE_BUFFER,
    TRANSFORM_FEEDBACK_BUFFER,
    ATOMIC_COUNTER_BUFFER,
    DISPATCH_INDIRECT_BUFFER,
    DRAW_INDIRECT_BUFFER,
    PIXEL_PACK_BUFFER,
    PIXEL_UNPACK_BUFFER,
    QUERY_BUFFER,
    TEXTURE_BUFFER,
    TRANSFORM_FEEDBACK_COUNTER_BUFFER,
    UNIFORM_BUFFER_OFFSET,
    VERTEX_ATTRIB_ARRAY_BUFFER,
    MAX_BUFFER_TYPE
};

template<typename _Ty>
struct BufferInfo
{
    BufferType type;
    unsigned int target;
    unsigned long size;
    _Ty* data;
    unsigned int usage;
};

template<typename _Ty>
class Buffer
{
public:
    using value_type = _Ty;
    using pointer = _Ty*;

    Buffer();
    Buffer(const BufferInfo<_Ty>& info);
    //Buffer(const Buffer& other);
    //Buffer(Buffer&& other);
    ~Buffer();

    Buffer& operator=(const BufferInfo<_Ty>& info);
    //Buffer& operator=(const Buffer& other);
    //Buffer& operator=(Buffer&& other);

    void bind() const;
    void unbind() const;

    unsigned int id() const;

private:
    unsigned int m_id;
    unsigned int m_target;
};

template<typename _Ty>
Buffer<_Ty>::Buffer()
{
    glGenBuffers(1, &m_id);
}

template<typename _Ty>
Buffer<_Ty>::Buffer(const BufferInfo<_Ty>& info)
{
    m_target = info.target;
    glGenBuffers(1, &m_id);
    bind();
    glBufferData(info.target, info.size, info.data, info.usage);
    //unbind();
    GL_CHECK_ERRORS();
}

template<typename _Ty>
Buffer<_Ty>::~Buffer()
{
    glDeleteBuffers(1, &m_id);
}

template<typename _Ty>
Buffer<_Ty>& Buffer<_Ty>::operator=(const BufferInfo<_Ty>& info)
{
    m_target = info.target;
    bind();
    glBufferData(info.target, info.size, info.data, info.usage);
    //unbind();
    return *this;
}

template<typename _Ty>
void Buffer<_Ty>::bind() const 
{
    glBindBuffer(m_target, m_id);
}

template<typename _Ty>
void Buffer<_Ty>::unbind() const
{
    glBindBuffer(m_target, 0);
}

template<typename _Ty>
unsigned int Buffer<_Ty>::id() const
{
    return m_id;
}

struct VertexArrayInfo
{
    unsigned int index;
    unsigned int size;
    unsigned int type;
    bool normalized;
    unsigned int stride;
    unsigned long offset;
};

class VertexArray
{
public:
    VertexArray();
    //VertexArray(const VertexArray& other);
    //VertexArray(VertexArray&& other);
    ~VertexArray();

    //VertexArray& operator=(const VertexArray& other);
    //VertexArray& operator=(VertexArray&& other);

    void createPointers(std::vector<VertexArrayInfo> info);
    void bind() const;
    void unbind() const;

    unsigned int id() const;

private:
    unsigned int m_id;
};


#endif // !_OPENGL_PIPELINE_H_