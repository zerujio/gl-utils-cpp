#include "buffer.hpp"

namespace glutils {

    GLint Buffer::getProperty(Buffer::Property property) const {
        GLint value;
        gl.GetNamedBufferParameteriv(getName(), static_cast<GLenum>(property), &value);
        return value;
    }

    GLint64 Buffer::getProperty64(Buffer::Property property) const {
        GLint64 value;
        gl.GetNamedBufferParameteri64v(getName(), static_cast<GLenum>(property), &value);
        return value;
    }

    GLenum Buffer::getAccess() const {
        return getProperty(Property::Access);
    }

    GLbitfield Buffer::getAccessFlags() const {
        return getProperty(Property::AccessFlags);
    }

    bool Buffer::getImmutable() const {
        return getProperty(Property::Immutable);
    }

    bool Buffer::getMapped() const {
        return getProperty(Property::Mapped);
    }

    GLsizeiptr Buffer::getMappedLength() const {
        return getProperty(Property::MapLength);
    }

    GLintptr Buffer::getMappedOffset() const {
        return getProperty(Property::MapOffset);
    }

    GLsizeiptr Buffer::getSize() const {
        return getProperty(Property::Size);
    }

    void Buffer::allocateData(GLsizeiptr size, Buffer::Usage usage, const void *init_data) const {
        gl.NamedBufferData(getName(), size, init_data, static_cast<GLenum>(usage));
    }


} // glutils