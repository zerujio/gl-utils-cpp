#include "glutils/buffer.hpp"
#include "glutils/gl.hpp"

#include <type_traits>

namespace GL {

auto BufferHandle::getParameter(BufferHandle::Parameter param) const -> GLint
{
    GLint value;
    glGetNamedBufferParameteriv(getName(), static_cast<GLenum>(param), &value);
    return value;
}

auto BufferHandle::getParameter64(BufferHandle::Parameter param) const -> GLint64
{
    GLint64 value;
    glGetNamedBufferParameteri64v(getName(), static_cast<GLenum>(param), &value);
    return value;
}

auto BufferHandle::getAccessMode() const -> BufferHandle::AccessMode
{
    return static_cast<AccessMode>(getParameter(Parameter::Access));
}

auto BufferHandle::getAccessFlags() const -> BufferHandle::AccessFlags
{
    return static_cast<AccessFlags>(getParameter(Parameter::AccessFlags));
}

auto BufferHandle::getImmutable() const -> bool
{
    return getParameter(Parameter::Immutable);
}

auto BufferHandle::getMapped() const -> bool
{
    return getParameter(Parameter::Mapped);
}

auto BufferHandle::getMapLength() const -> GLsizeiptr
{
    return getParameter64(Parameter::MapLength);
}

auto BufferHandle::getMapOffset() const -> GLintptr
{
    return getParameter64(Parameter::MapOffset);
}

auto BufferHandle::getSize() const -> GLsizeiptr
{
    return getParameter(Parameter::Size);
}

auto BufferHandle::getStorageFlags() const -> BufferHandle::StorageFlags
{
    return static_cast<StorageFlags>(getParameter(Parameter::StorageFlags));
}

auto BufferHandle::getUsage() const -> BufferHandle::Usage
{
    return static_cast<Usage>(getParameter(Parameter::Usage));
}

void BufferHandle::allocate(GLsizeiptr size, BufferHandle::Usage usage, const void *init_data) const
{
    glNamedBufferData(getName(), size, init_data, static_cast<GLenum>(usage));
}

void BufferHandle::allocateImmutable(GLsizeiptr size, BufferHandle::StorageFlags flags, const void *init_data) const
{
    glNamedBufferStorage(getName(), size, init_data, static_cast<GLbitfield>(flags));
}

void BufferHandle::write(GLintptr offset, GLsizeiptr size, const void *data) const
{
    glNamedBufferSubData(getName(), offset, size, data);
}

void BufferHandle::read(GLintptr offset, GLsizeiptr size, void *data) const
{
    glGetNamedBufferSubData(getName(), offset, size, data);
}

auto BufferHandle::map(BufferHandle::AccessMode access) const -> void *
{
    return glMapNamedBuffer(getName(), static_cast<GLbitfield>(access));
}

auto BufferHandle::mapRange(GLintptr offset, GLsizeiptr length, BufferHandle::AccessFlags access) const -> void *
{
    return glMapNamedBufferRange(getName(), offset, length, static_cast<GLbitfield>(access));
}

void BufferHandle::unmap() const
{
    glUnmapNamedBuffer(getName());
}

auto BufferHandle::create() -> BufferHandle
{
    GLuint name;
    glCreateBuffers(1, &name);
    return BufferHandle{name};
}

void BufferHandle::destroy(BufferHandle buffer)
{
    glDeleteBuffers(1, &buffer.m_name);
}

void BufferHandle::bindBase(BufferHandle::IndexedTarget target, GLuint index) const
{
    glBindBufferBase(static_cast<GLenum>(target), index, m_name);
}

void BufferHandle::bindRange(BufferHandle::IndexedTarget target, GLuint index, GLintptr offset, GLsizeiptr size) const
{
    glBindBufferRange(static_cast<GLenum>(target), index, m_name, offset, size);
}

void
BufferHandle::copy(BufferHandle read_buffer, BufferHandle write_buffer, GLintptr read_offset, GLintptr write_offset,
                   GLsizeiptr size)
{
    glCopyNamedBufferSubData(read_buffer.getName(), write_buffer.getName(), read_offset, write_offset, size);
}

void
BufferHandle::s_bindRange(BufferHandle::IndexedTarget target, GLuint first_binding, GLsizei count,
                          const GLuint *buffers,
                          const GLintptr *offsets, const GLintptr *sizes)
{
    glBindBuffersRange(static_cast<GLenum>(target), first_binding, count, buffers, offsets, sizes);
}

void BufferHandle::s_bindBases(BufferHandle::IndexedTarget target, GLuint first_binding, GLsizei count,
                               const GLuint *buffers)
{
    glBindBuffersBase(static_cast<GLenum>(target), first_binding, count, buffers);
}

template<class T>
auto enumOR(T l, T r) -> T
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(l)
                          | static_cast<std::underlying_type_t<T>>(r));
}

template<class T>
auto enumAND(T l, T r) -> T
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(l)
                          & static_cast<std::underlying_type_t<T>>(r));
}

auto operator|(BufferHandle::AccessFlags l, BufferHandle::AccessFlags r) -> BufferHandle::AccessFlags
{
    return enumOR(l, r);
}

auto operator&(BufferHandle::AccessFlags l, BufferHandle::AccessFlags r) -> BufferHandle::AccessFlags
{
    return enumAND(l, r);
}

auto operator|(BufferHandle::StorageFlags l, BufferHandle::StorageFlags r) -> BufferHandle::StorageFlags
{
    return enumOR(l, r);
}

auto operator&(BufferHandle::StorageFlags l, BufferHandle::StorageFlags r) -> BufferHandle::StorageFlags
{
    return enumAND(l, r);
}

} // GL