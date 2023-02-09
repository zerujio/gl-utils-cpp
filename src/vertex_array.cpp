#include "glutils/vertex_array.hpp"
#include "glutils/gl.hpp"

namespace GL {
auto VertexArrayHandle::create() -> VertexArrayHandle
{
    GLuint name;
    gl.CreateVertexArrays(1, &name);
    return VertexArrayHandle{name};
}

void VertexArrayHandle::destroy(GL::VertexArrayHandle vertex_array)
{
    gl.DeleteVertexArrays(1, &vertex_array.m_name);
}

void VertexArrayHandle::bind() const
{
    gl.BindVertexArray(getName());
}

void VertexArrayHandle::bindVertexBuffer(GLuint binding_index, BufferHandle buffer, GLintptr offset, GLsizei stride) const
{
    gl.VertexArrayVertexBuffer(getName(), binding_index, buffer.getName(), offset, stride);
}

void VertexArrayHandle::bindElementBuffer(BufferHandle buffer) const
{
    gl.VertexArrayElementBuffer(getName(), buffer.getName());
}

void VertexArrayHandle::bindAttribute(GLuint attribute_index, GLuint binding_index) const
{
    gl.VertexArrayAttribBinding(getName(), attribute_index, binding_index);
}

void VertexArrayHandle::enableAttribute(GLuint attribute_index) const
{
    gl.EnableVertexArrayAttrib(getName(), attribute_index);
}

void VertexArrayHandle::disableAttribute(GLuint attribute_index) const
{
    gl.DisableVertexArrayAttrib(getName(), attribute_index);
}

void VertexArrayHandle::setBindingDivisor(GLuint binding_index, GLuint divisor) const
{
    gl.VertexArrayBindingDivisor(getName(), binding_index, divisor);
}

void VertexArrayHandle::setAttribFormat(GLuint attribute_index, VertexArrayHandle::AttribSize size,
                                        VertexArrayHandle::AttribType type, bool normalized,
                                        GLuint relative_offset) const
{
    gl.VertexArrayAttribFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                               normalized, relative_offset);
}

void VertexArrayHandle::setAttribIFormat(GLuint attribute_index, VertexArrayHandle::AttribSize size,
                                         VertexArrayHandle::AttribType type, GLuint relative_offset) const
{
    gl.VertexArrayAttribIFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                                relative_offset);
}

void VertexArrayHandle::setAttribLFormat(GLuint attribute_index, VertexArrayHandle::AttribSize size,
                                         VertexArrayHandle::AttribType type, GLuint relative_offset) const
{
    gl.VertexArrayAttribLFormat(getName(), attribute_index, static_cast<int>(size), static_cast<GLenum>(type),
                                relative_offset);
}

void
VertexArrayHandle::bindVertexBuffers(GLuint first_index, GLsizei count, const BufferHandle *buffers, const GLintptr *offsets,
                                     const GLsizei *strides) const
{
    gl.VertexArrayVertexBuffers(getName(), first_index, count, reinterpret_cast<const GLuint *>(buffers), offsets,
                                strides);
}


} // GL