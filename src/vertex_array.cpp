#include "glutils/vertex_array.hpp"

namespace glutils {
    void VertexArray::bind() const
    {
        gl.BindVertexArray(getName());
    }

    void VertexArray::bindVertexBuffer(GLuint binding_index, Buffer buffer, GLintptr offset, GLsizei stride) const
    {
        gl.VertexArrayVertexBuffer(getName(), binding_index, buffer.getName(), offset, stride);
    }

    void VertexArray::bindElementBuffer(Buffer buffer) const
    {
        gl.VertexArrayElementBuffer(getName(), buffer.getName());
    }

    void VertexArray::bindAttribute(GLuint attribute_index, GLuint binding_index) const
    {
        gl.VertexArrayAttribBinding(getName(), attribute_index, binding_index);
    }

    void VertexArray::enableAttribute(GLuint attribute_index) const
    {
        gl.EnableVertexArrayAttrib(getName(), attribute_index);
    }

    void VertexArray::disableAttribute(GLuint attribute_index) const
    {
        gl.DisableVertexArrayAttrib(getName(), attribute_index);
    }

    void VertexArray::setBindingDivisor(GLuint binding_index, GLuint divisor) const
    {
        gl.VertexArrayBindingDivisor(getName(), binding_index, divisor);
    }

    void VertexArray::setAttribFormat(GLuint attribute_index, VertexArray::AttribSize size,
                                      VertexArray::AttribType type, bool normalized,
                                      GLuint relative_offset) const
    {
        gl.VertexArrayAttribFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                                   normalized, relative_offset);
    }

    void VertexArray::setAttribIFormat(GLuint attribute_index, VertexArray::AttribSize size,
                                       VertexArray::AttribType type, GLuint relative_offset) const
    {
        gl.VertexArrayAttribIFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                                    relative_offset);
    }

    void VertexArray::setAttribLFormat(GLuint attribute_index, VertexArray::AttribSize size,
                                       VertexArray::AttribType type, GLuint relative_offset) const
    {
        gl.VertexArrayAttribLFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                                    relative_offset);
    }

    void
    VertexArray::bindVertexBuffers(GLuint first_index, GLsizei count, const Buffer *buffers, const GLintptr *offsets,
                                   const GLsizei *strides) const
    {
        gl.VertexArrayVertexBuffers(getName(), first_index, count, reinterpret_cast<const GLuint *>(buffers), offsets,
                                    strides);
    }


} // glutils