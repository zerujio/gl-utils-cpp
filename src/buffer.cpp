#include "glutils/buffer.hpp"

namespace glutils {

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

    GLenum Buffer::getAccess() const {
        return getParameter(Parameter::Access);
    }

    GLbitfield Buffer::getAccessFlags() const {
        return getParameter(Parameter::AccessFlags);
    }

    bool Buffer::getImmutable() const {
        return getParameter(Parameter::Immutable);
    }

    bool Buffer::getMapped() const {
        return getParameter(Parameter::Mapped);
    }

    GLsizeiptr Buffer::getMapLength() const {
        return getParameter(Parameter::MapLength);
    }

    GLintptr Buffer::getMapOffset() const {
        return getParameter(Parameter::MapOffset);
    }

    GLsizeiptr Buffer::getSize() const {
        return getParameter(Parameter::Size);
    }

    GLbitfield Buffer::getStorageFlags() const {
        return getParameter(Parameter::StorageFlags);
    }

    void Buffer::allocateData(GLsizeiptr size, Buffer::Usage usage, const void *init_data) const {
        gl.NamedBufferData(getName(), size, init_data, static_cast<GLenum>(usage));
    }


} // glutils