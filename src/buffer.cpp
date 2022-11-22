#include "glutils/buffer.hpp"
#include "glutils/gl.hpp"

#include <type_traits>

namespace glutils {

    auto Buffer::getParameter(Buffer::Parameter param) const -> GLint
    {
        GLint value;
        gl.GetNamedBufferParameteriv(getName(), static_cast<GLenum>(param), &value);
        return value;
    }

    auto Buffer::getParameter64(Buffer::Parameter param) const -> GLint64
    {
        GLint64 value;
        gl.GetNamedBufferParameteri64v(getName(), static_cast<GLenum>(param), &value);
        return value;
    }

    auto Buffer::getAccessMode() const -> Buffer::AccessMode
    {
        return static_cast<AccessMode>(getParameter(Parameter::Access));
    }

    auto Buffer::getAccessFlags() const -> Buffer::AccessFlags
    {
        return static_cast<AccessFlags>(getParameter(Parameter::AccessFlags));
    }

    auto Buffer::getImmutable() const -> bool
    {
        return getParameter(Parameter::Immutable);
    }

    auto Buffer::getMapped() const -> bool
    {
        return getParameter(Parameter::Mapped);
    }

    auto Buffer::getMapLength() const -> GLsizeiptr
    {
        return getParameter64(Parameter::MapLength);
    }

    auto Buffer::getMapOffset() const -> GLintptr
    {
        return getParameter64(Parameter::MapOffset);
    }

    auto Buffer::getSize() const -> GLsizeiptr
    {
        return getParameter(Parameter::Size);
    }

    auto Buffer::getStorageFlags() const -> Buffer::StorageFlags
    {
        return static_cast<StorageFlags>(getParameter(Parameter::StorageFlags));
    }

    auto Buffer::getUsage() const -> Buffer::Usage
    {
        return static_cast<Usage>(getParameter(Parameter::Usage));
    }

    void Buffer::allocate(GLsizeiptr size, Buffer::Usage usage, const void *init_data) const
    {
        gl.NamedBufferData(getName(), size, init_data, static_cast<GLenum>(usage));
    }

    void Buffer::allocateImmutable(GLsizeiptr size, Buffer::StorageFlags flags, const void *init_data) const
    {
        gl.NamedBufferStorage(getName(), size, init_data, static_cast<GLbitfield>(flags));
    }

    void Buffer::write(GLintptr offset, GLsizeiptr size, const void *data) const
    {
        gl.NamedBufferSubData(getName(), offset, size, data);
    }

    void Buffer::read(GLintptr offset, GLsizeiptr size, void *data) const
    {
        gl.GetNamedBufferSubData(getName(), offset, size, data);
    }

    auto Buffer::map(Buffer::AccessMode access) const -> void *
    {
        return gl.MapNamedBuffer(getName(), static_cast<GLbitfield>(access));
    }

    auto Buffer::mapRange(GLintptr offset, GLsizeiptr length, Buffer::AccessFlags access) const -> void *
    {
        return gl.MapNamedBufferRange(getName(), offset, length, static_cast<GLbitfield>(access));
    }

    void Buffer::unmap() const
    {
        gl.UnmapNamedBuffer(getName());
    }

    auto Buffer::create() -> Buffer
    {
        GLuint name;
        gl.CreateBuffers(1, &name);
        return {name};
    }

    void Buffer::destroy(Buffer buffer)
    {
        gl.DeleteBuffers(1, &buffer.m_name);
    }

    void Buffer::bindBase(Buffer::IndexedTarget target, GLuint index) const
    {
        gl.BindBufferBase(static_cast<GLenum>(target), index, m_name);
    }

    void Buffer::bindRange(Buffer::IndexedTarget target, GLuint index, GLintptr offset, GLsizeiptr size) const
    {
        gl.BindBufferRange(static_cast<GLenum>(target), index, m_name, offset, size);
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

    auto operator|(Buffer::AccessFlags l, Buffer::AccessFlags r) -> Buffer::AccessFlags
    {
        return enumOR(l, r);
    }

    auto operator&(Buffer::AccessFlags l, Buffer::AccessFlags r) -> Buffer::AccessFlags
    {
        return enumAND(l, r);
    }

    auto operator|(Buffer::StorageFlags l, Buffer::StorageFlags r) -> Buffer::StorageFlags
    {
        return enumOR(l, r);
    }

    auto operator&(Buffer::StorageFlags l, Buffer::StorageFlags r) -> Buffer::StorageFlags
    {
        return enumAND(l, r);
    }

} // glutils