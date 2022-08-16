#ifndef GLUTILS_BUFFER_HPP
#define GLUTILS_BUFFER_HPP

#include "proxy.hpp"

namespace glutils {

    GLuint createBuffer();
    void destroyBuffer(GLuint name);
    bool validateBuffer(GLuint name);

    class Buffer : Proxy<createBuffer, destroyBuffer, validateBuffer> {
    public:
        using Proxy::Proxy;

        enum class Property {
            Access      = GL_BUFFER_ACCESS,
            AccessFlags = GL_BUFFER_ACCESS_FLAGS,
            Immutable   = GL_BUFFER_IMMUTABLE_STORAGE,
            Mapped      = GL_BUFFER_MAPPED,
            MapLength   = GL_BUFFER_MAP_LENGTH,
            MapOffset   = GL_BUFFER_MAP_OFFSET,
            Size        = GL_BUFFER_SIZE,
            StorageFlags= GL_BUFFER_STORAGE_FLAGS,
            BufferUsage = GL_BUFFER_USAGE
        };

        /// Query the value of some property.
        [[nodiscard]] GLint getProperty(Property property) const;

        [[nodiscard]] GLint64 getProperty64(Property property) const;

        [[nodiscard]] GLenum getAccess() const;

        [[nodiscard]] GLbitfield getAccessFlags() const;

        [[nodiscard]] bool getImmutable() const;

        [[nodiscard]] bool getMapped() const;

        [[nodiscard]] GLsizeiptr getMappedLength() const;

        [[nodiscard]] GLintptr getMappedOffset() const;

        [[nodiscard]] GLsizeiptr getSize() const;

        enum class Usage {
            StaticDraw  = GL_STATIC_DRAW,
            StaticRead  = GL_STATIC_READ,
            StaticCopy  = GL_STATIC_COPY,
            DynamicDraw = GL_DYNAMIC_DRAW,
            DynamicRead = GL_DYNAMIC_READ,
            DynamicCopy = GL_DYNAMIC_COPY,
            StreamDraw  = GL_STREAM_DRAW,
            StreamRead  = GL_STREAM_READ,
            StreamCopy  = GL_STREAM_COPY
        };

        /// Allocate mutable storage.
        /**
         * Wraps glBufferData
         * @param size Size to allocate, in bytes.
         * @param usage Usage enum.
         * @param init_data Data to initialize the storage with.
         */
        void allocateData(GLsizeiptr size, Usage usage, const void* init_data = nullptr) const;
    };

} // glutils

#endif //GLUTILS_BUFFER_HPP
