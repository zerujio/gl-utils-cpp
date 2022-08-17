#ifndef GLUTILS_BUFFER_HPP
#define GLUTILS_BUFFER_HPP

#include "handle.hpp"

namespace glutils {

    /// Wraps glCreateBuffers().
    GLuint createBuffer();

    /// Wraps glDeleteBuffers().
    void destroyBuffer(GLuint name);

    /// Wraps glIsBuffer().
    bool validateBuffer(GLuint name);

    /// Wraps "NamedBuffer" OpenGL functions.
    class Buffer : Handle<createBuffer, destroyBuffer, validateBuffer> {
    public:

        enum class Parameter {
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

        /// Return parameters of a buffer object
        /**
         * Wraps glNamedBufferParameteriv().
         *
         * @param pname the enum value of the parameter to query.
         * @return the current value of the parameter.
         */
        [[nodiscard]] GLint getParameter(Parameter pname) const;

        /// Same as getParameter(), but returns a 64 bit integer.
        [[nodiscard]] GLint64 getParameter64(Parameter pname) const;

        /// Query the GL_BUFFER_ACCESS parameter.
        /**
         * If the buffer was mapped with glMapBufferRange(), the access policy is determined by translating the bits in
         * that access parameter to one of the supported enums for glMapBuffer() as described in the OpenGL Specification.
         *
         * @return the access policy set while mapping the buffer object (the value of the @p access parameter bitfield
         * passed to glMapBuffer).
         */
        [[nodiscard]] GLenum getAccess() const;

        /// Query the GL_BUFFER_ACCESS_FLAGS parameter.
        /**
         * If the buffer was mapped with glMapBuffer, the access policy is determined by translating the enums in that
         * access parameter to the corresponding bits for glMapBufferRange as described in the OpenGL Specification. The
         * initial value is zero.
         *
         * @return the access policy set while mapping the buffer object (the value of the @p access parameter bitfield
         * passed to glMapBufferRange).
         */
        [[nodiscard]] GLbitfield getAccessFlags() const;

        /// Query the GL_BUFFER_IMMUTABLE_STORAGE parameter.
        /**
         * The initial value is GL_FALSE.
         *
         * @return boolean flag indicating whether the buffer object is immutable.
         */
        [[nodiscard]] bool getImmutable() const;

        /// Query the GL_BUFFER_MAPPED parameter.
        /**
         * The initial value is GL_FALSE.
         *
         * @return a flag indicating whether the buffer object is currently mapped.
         */
        [[nodiscard]] bool getMapped() const;

        /// Query the GL_BUFFER_MAP_LENGTH parameter.
        /**
         * The i64v versions of these queries should be used for this parameter. The initial value is zero.
         *
         * @return the length of the mapping into the buffer object established with glMapBuffer*.
         */
        [[nodiscard]] GLsizeiptr getMapLength() const;

        /// Query the GL_BUFFER_MAP_OFFSET parameter.
        /**
         * The initial value is 0.
         * @return the size of the buffer object, measured in bytes.
         */
        [[nodiscard]] GLintptr getMapOffset() const;

        /// Query the GL_BUFFER_SIZE parameter.
        /**
         * The initial value is 0.
         *
         * @return the size of the buffer object, measured in bytes. The
         */
        [[nodiscard]] GLsizeiptr getSize() const;

        /// Query the GL_BUFFER_STORAGE_FLAGS parameter.
        /**
         *  If the buffer object is immutable, the value returned will be that specified when the data store was
         *  established with glBufferStorage. If the data store was established with glBufferData, the value will
         *  be GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT.
         *
         *  The initial value is zero.
         *
         * @return a bitfield indicating the storage flags for the buffer object.
         */
        [[nodiscard]] GLbitfield getStorageFlags() const;

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

        /// Query the GL_BUFFER_USAGE parameter.
        /**
         *  The initial value is GL_STATIC_DRAW.
         *
         * @return the buffer object's usage pattern.
         */
        [[nodiscard]] Usage getUsage() const;

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
