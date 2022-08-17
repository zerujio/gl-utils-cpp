#include "glutils/buffer.hpp"

namespace glutils {

    GLuint impl::createBuffer() {
        GLuint buf;
        gl.CreateBuffers(1, &buf);
        return buf;
    }

    void impl::destroyBuffer(GLuint name) {
      gl.DeleteBuffers(1, &name);
    }

    bool impl::validateBuffer(GLuint name) {
        gl.IsBuffer(name);
    }

    GLint Buffer::getParameter(Buffer::Parameter param) const {
        GLint value;
        gl.GetNamedBufferParameteriv(getName(), static_cast<GLenum>(param), &value);
        return value;
    }

    GLint64 Buffer::getParameter64(Buffer::Parameter param) const {
        GLint64 value;
        gl.GetNamedBufferParameteri64v(getName(), static_cast<GLenum>(param), &value);
        return value;
    }

    Buffer::AccessMode Buffer::getAccessMode() const {
        return static_cast<AccessMode>(getParameter(Parameter::Access));
    }

    Buffer::AccessFlags Buffer::getAccessFlags() const {
        return static_cast<AccessFlags>(getParameter(Parameter::AccessFlags));
    }

    bool Buffer::getImmutable() const {
        return getParameter(Parameter::Immutable);
    }

    bool Buffer::getMapped() const {
        return getParameter(Parameter::Mapped);
    }

    GLsizeiptr Buffer::getMapLength() const {
        return getParameter64(Parameter::MapLength);
    }

    GLintptr Buffer::getMapOffset() const {
        return getParameter64(Parameter::MapOffset);
    }

    GLsizeiptr Buffer::getSize() const {
        return getParameter(Parameter::Size);
    }

    Buffer::StorageFlags Buffer::getStorageFlags() const {
        return static_cast<StorageFlags>(getParameter(Parameter::StorageFlags));
    }

    Buffer::Usage Buffer::getUsage() const {
        return static_cast<Usage>(getParameter(Parameter::Usage));
    }

    void Buffer::allocate(GLsizeiptr size, Buffer::Usage usage, const void *init_data) const {
        gl.NamedBufferData(getName(), size, init_data, static_cast<GLenum>(usage));
    }

    void Buffer::allocateImmutable(GLsizeiptr size, Buffer::StorageFlags flags, const void *init_data) const {
        gl.NamedBufferStorage(getName(), size, init_data, static_cast<GLbitfield>(flags));
    }

    void Buffer::write(GLintptr offset, GLsizeiptr size, const void *data) const {
        gl.NamedBufferSubData(getName(), offset, size, data);
    }

    void Buffer::read(GLintptr offset, GLsizeiptr size, void *data) const {
        gl.GetNamedBufferSubData(getName(), offset, size, data);
    }

    void *Buffer::map(Buffer::AccessMode access) const {
        gl.MapNamedBuffer(getName(), static_cast<GLbitfield>(access));
    }

    void *Buffer::mapRange(GLintptr offset, GLsizeiptr length, Buffer::AccessFlags access) const {
        gl.MapNamedBufferRange(getName(), offset, length, static_cast<GLbitfield>(access));
    }

    void Buffer::unmap() const {
        gl.UnmapNamedBuffer(getName());
    }

    // struct BufferOffset

    void BufferOffset::write(GLsizeiptr size, const void *data) const {
        buffer.write(offset, size, data);
    }

    void BufferOffset::read(GLsizeiptr size, void *data) const {
        buffer.read(offset, size, data);
    }

    void *BufferOffset::map(GLsizeiptr length, Buffer::AccessFlags access) const {
        buffer.mapRange(offset, length, access);
    }

    // struct BufferRange

    void BufferRange::write(const void *data) const {
        BufferOffset::write(size, data);
    }

    void BufferRange::read(void *data) const {
        BufferOffset::read(size, data);
    }

    void *BufferRange::map(Buffer::AccessFlags access) const {
        BufferOffset::map(size, access);
    }

} // glutils