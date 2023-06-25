#include "glutils/vertex_array.hpp"
#include "glutils/gl.hpp"

namespace GL {
auto VertexArrayHandle::create() -> VertexArrayHandle
{
    GLuint name;
    glCreateVertexArrays(1, &name);
    return VertexArrayHandle{name};
}

void VertexArrayHandle::destroy(GL::VertexArrayHandle vertex_array)
{
    glDeleteVertexArrays(1, &vertex_array.m_name);
}

void VertexArrayHandle::bind() const
{
    glBindVertexArray(getName());
}

void
VertexArrayHandle::bindVertexBuffer(GLuint binding_index, BufferHandle buffer, GLintptr offset, GLsizei stride) const
{
    glVertexArrayVertexBuffer(getName(), binding_index, buffer.getName(), offset, stride);
}

void VertexArrayHandle::bindElementBuffer(BufferHandle buffer) const
{
    glVertexArrayElementBuffer(getName(), buffer.getName());
}

void VertexArrayHandle::bindAttribute(GLuint attribute_index, GLuint binding_index) const
{
    glVertexArrayAttribBinding(getName(), attribute_index, binding_index);
}

void VertexArrayHandle::enableAttribute(GLuint attribute_index) const
{
    glEnableVertexArrayAttrib(getName(), attribute_index);
}

void VertexArrayHandle::disableAttribute(GLuint attribute_index) const
{
    glDisableVertexArrayAttrib(getName(), attribute_index);
}

void VertexArrayHandle::setBindingDivisor(GLuint binding_index, GLuint divisor) const
{
    glVertexArrayBindingDivisor(getName(), binding_index, divisor);
}

void VertexArrayHandle::setAttribFormat(GLuint attribute_index, VertexArrayHandle::AttribSize size,
                                        VertexArrayHandle::AttribType type, bool normalized,
                                        GLuint relative_offset) const
{
    glVertexArrayAttribFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                              normalized, relative_offset);
}

void VertexArrayHandle::setAttribIFormat(GLuint attribute_index, VertexArrayHandle::AttribSize size,
                                         VertexArrayHandle::AttribType type, GLuint relative_offset) const
{
    glVertexArrayAttribIFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                               relative_offset);
}

void VertexArrayHandle::setAttribLFormat(GLuint attribute_index, VertexArrayHandle::AttribSize size,
                                         VertexArrayHandle::AttribType type, GLuint relative_offset) const
{
    glVertexArrayAttribLFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                               relative_offset);
}

void
VertexArrayHandle::bindVertexBuffers(GLuint first_index, GLsizei count, const BufferHandle *buffers,
                                     const GLintptr *offsets,
                                     const GLsizei *strides) const
{
    glVertexArrayVertexBuffers(getName(), first_index, count, reinterpret_cast<const GLuint *>(buffers), offsets,
                               strides);
}


} // GL