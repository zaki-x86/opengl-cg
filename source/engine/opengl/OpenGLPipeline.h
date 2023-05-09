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
    std::vector<_Ty> data;
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
    Buffer(const Buffer& other) = default;
    Buffer(Buffer&& other) = default;
    ~Buffer();

    Buffer& operator=(const BufferInfo<_Ty>& info);
    Buffer& operator=(BufferInfo<_Ty>&& info);
    Buffer& operator=(const Buffer& other) = default;
    Buffer& operator=(Buffer&& other) = default;

    void setBuffer(const BufferInfo<_Ty>& info);

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
    glBufferData(info.target, info.size, info.data.data(), info.usage);
    
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
    glBufferData(info.target, info.size, info.data.data(), info.usage);
    
    //unbind();
    return *this;
}

template<typename _Ty>
Buffer<_Ty>& Buffer<_Ty>::operator=(BufferInfo<_Ty>&& info)
{
    m_target = info.target;
    bind();
    glBufferData(info.target, info.size, info.data.data(), info.usage);
    
    //unbind();
    return *this;
}

template<typename _Ty>
void Buffer<_Ty>::setBuffer(const BufferInfo<_Ty>& info) {
    m_target = info.target;
    bind();
    glBufferData(info.target, info.size, info.data.data(), info.usage);
    
    //unbind();
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
    GLuint index;
    GLuint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    unsigned long offset;
};

class VertexArray {

 public:

  VertexArray() = default;

  VertexArray(const VertexArray& other) = default;

  VertexArray(VertexArray&& other) { *this = std::move(other); }

  ~VertexArray() { if (m_id) glDeleteVertexArrays(1, &m_id); }

  VertexArray& operator=(const VertexArray& other) = default;

  VertexArray& operator=(VertexArray&& other) {
    if (this != &other) {
      if (m_id) glDeleteVertexArrays(1, &m_id);

      m_id = std::exchange(other.m_id, 0);
    }
    return *this;
  }

  /**
   * @brief Binds the VertexArray.
   */
  void bind() const { glBindVertexArray(m_id); }

  /**
   * @brief Specifies how OpenGL should interpret the vertex buffer data whenever a draw call is made.
   * @param vbo The vertex buffer object to be binded.
   * @param layout Specifies the index of the generic vertex attribute to be modified. Must match the layout in the shader.
   * @param components Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
   * @param type Type of the data.
   * @param stride Specifies the byte offset between consecutive generic vertex attributes.
   * @param offset Specifies a offset of the first component of the first generic vertex attribute in the array in the data store.
   * @param normalize Specifies whether fixed-point data values should be normalized.
   */
  template<typename _Ty>
  void linkAttrib(const Buffer<_Ty>& vbo, const VertexArrayInfo&) const;

  /**
   * @brief Specifies how OpenGL should interpret the vertex buffer data whenever a draw call is made. IT DOESN'T BIND ANYTHING!
   * @param layout Specifies the index of the generic vertex attribute to be modified. Must match the layout in the shader.
   * @param components Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
   * @param type Type of the data.
   * @param stride Specifies the byte offset between consecutive generic vertex attributes.
   * @param offset Specifies a offset of the first component of the first generic vertex attribute in the array in the data store.
   * @param normalize Specifies whether fixed-point data values should be normalized.
   */
  void linkAttribFast(const VertexArrayInfo& info) const;

  /**
   * @brief Generates the vertex array buffer.
   */
  void create();

  /**
   * @brief Unbinds the VertexArray.
   */
  void unbind() const { glBindVertexArray(0); }

  GLuint id() const { return m_id; }

 private:

  GLuint m_id {};
};


#endif // !_OPENGL_PIPELINE_H_