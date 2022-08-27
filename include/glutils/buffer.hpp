#ifndef GLUTILS_BUFFER_HPP
#define GLUTILS_BUFFER_HPP

#include "handle.hpp"

#include <type_traits>

namespace glutils {


    /// Wraps "NamedBuffer" OpenGL functions.
    class Buffer : public Handle<Buffer, &GladGLContext::CreateBuffers, &GladGLContext::DeleteBuffers, &GladGLContext::IsBuffer>
{
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
            Usage = GL_BUFFER_USAGE
        };

        /// Return parameters of a buffer object
        /**
         * Wraps glNamedBufferParameteriv().
         *
         * @param pname the enum value of the parameter to query.
         * @return the current value of the parameter.
         */
        [[nodiscard]]
        auto getParameter(Parameter pname) const -> GLint;

        /// Same as getParameter(), but returns a 64 bit integer.
        [[nodiscard]]
        auto getParameter64(Parameter pname) const -> GLint64;

        /// Access modes for glMapBuffer.
        enum class AccessMode {
            read_only   = GL_READ_ONLY,
            write_only  = GL_WRITE_ONLY,
            read_write  = GL_READ_WRITE
        };

        /// Query the GL_BUFFER_ACCESS parameter.
        /**
         * If the buffer was mapped with glMapBufferRange(), the access policy is determined by translating the bits in
         * that access parameter to one of the supported enums for glMapBuffer() as described in the OpenGL Specification.
         *
         * @return the access policy set while mapping the buffer object (the value of the @p access parameter bitfield
         * passed to glMapBuffer).
         */
        [[nodiscard]] AccessMode getAccessMode() const;

        /// Access flags for glMapBufferRange.
        enum class AccessFlags {
            read        = GL_MAP_READ_BIT,
            write       = GL_MAP_WRITE_BIT,
            persistent  = GL_MAP_PERSISTENT_BIT,
            coherent    = GL_MAP_COHERENT_BIT,
            invalidate_range    = GL_MAP_INVALIDATE_RANGE_BIT,
            invalidate_buffer   = GL_MAP_INVALIDATE_BUFFER_BIT,
            flush_explicit      = GL_MAP_FLUSH_EXPLICIT_BIT,
            unsynchronized      = GL_MAP_UNSYNCHRONIZED_BIT
        };

        /// Query the GL_BUFFER_ACCESS_FLAGS parameter.
        /**
         * If the buffer was mapped with glMapBuffer, the access policy is determined by translating the enums in that
         * access parameter to the corresponding bits for glMapBufferRange as described in the OpenGL Specification. The
         * initial value is zero.
         *
         * @return the access policy set while mapping the buffer object (the value of the @p access parameter bitfield
         * passed to glMapBufferRange).
         */
        [[nodiscard]]
        auto getAccessFlags() const -> AccessFlags;

        /// Query the GL_BUFFER_IMMUTABLE_STORAGE parameter.
        /**
         * The initial value is GL_FALSE.
         *
         * @return boolean flag indicating whether the buffer object is immutable.
         */
        [[nodiscard]]
        auto getImmutable() const -> bool;

        /// Query the GL_BUFFER_MAPPED parameter.
        /**
         * The initial value is GL_FALSE.
         *
         * @return a flag indicating whether the buffer object is currently mapped.
         */
        [[nodiscard]]
        auto getMapped() const -> bool;

        /// Query the GL_BUFFER_MAP_LENGTH parameter.
        /**
         * The i64v versions of these queries should be used for this parameter. The initial value is zero.
         *
         * @return the length of the mapping into the buffer object established with glMapBuffer*.
         */
        [[nodiscard]]
        auto getMapLength() const -> GLsizeiptr;

        /// Query the GL_BUFFER_MAP_OFFSET parameter.
        /**
         * The initial value is 0.
         * @return the size of the buffer object, measured in bytes.
         */
        [[nodiscard]]
        auto getMapOffset() const -> GLintptr;

        /// Query the GL_BUFFER_SIZE parameter.
        /**
         * The initial value is 0.
         *
         * @return the size of the buffer object, measured in bytes. The
         */
        [[nodiscard]]
        auto getSize() const -> GLsizeiptr;

        enum class Usage {
            static_draw     = GL_STATIC_DRAW,
            static_read     = GL_STATIC_READ,
            static_copy     = GL_STATIC_COPY,
            dynamic_draw    = GL_DYNAMIC_DRAW,
            dynamic_read    = GL_DYNAMIC_READ,
            dynamic_copy    = GL_DYNAMIC_COPY,
            stream_draw     = GL_STREAM_DRAW,
            stream_read     = GL_STREAM_READ,
            stream_copy     = GL_STREAM_COPY
        };

        /// Query the GL_BUFFER_USAGE parameter.
        /**
         *  The initial value is GL_STATIC_DRAW.
         *
         * @return the buffer object's usage pattern.
         */
        [[nodiscard]]
        auto getUsage() const -> Usage;

        enum class StorageFlags {
            dynamic_storage = GL_DYNAMIC_STORAGE_BIT,
            map_read        = GL_DYNAMIC_READ,
            map_write       = GL_MAP_WRITE_BIT,
            map_persistent  = GL_MAP_PERSISTENT_BIT,
            map_coherent    = GL_MAP_COHERENT_BIT,
            client_storage  = GL_CLIENT_STORAGE_BIT,
        };

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
        [[nodiscard]]
        auto getStorageFlags() const -> StorageFlags;

        /// (Re)allocate and optionally initialize mutable storage.
        /**
         * Wraps glBufferData.
         * @param size Size to allocate, in bytes.
         * @param usage Usage enum.
         * @param init_data Data to initialize the storage with, if not null.
         */
        void allocate(GLsizeiptr size, Usage usage, const void* init_data = nullptr) const;

        /// Allocate and optionally initialize immutable (non-resizable) storage.
        /**
         * Wraps glBufferStorage.
         * @param size Size to allocate, in bytes.
         * @param flags storage flags.
         * @param init_data data to initialize the store with, if not null.
         */
        void allocateImmutable(GLsizeiptr size, StorageFlags flags, const void *init_data = nullptr) const;

        /// Copy data from host memory to GPU buffer.
        /**
         * Wraps glBufferSubData
         * @param offset byte offset into the buffer storage.
         * @param size in bytes.
         * @param data pointer to the data to write.
         */
        void write(GLintptr offset, GLsizeiptr size, const void *data) const;

        /// Copy data from GPU buffer to host memory.
        /**
         * Wraps glGetBufferSubData.
         * @param offset byte offset into the buffer storage.
         * @param size in bytes.
         * @param data pointer to host memory; data read from the buffer will be written here.
         */
        void read(GLintptr offset, GLsizeiptr size, void *data) const;

        /// Map the whole buffer to the host address space.
        /**
         * Wraps glMapBuffer.
         * @param access Access policy.
         * @return a valid pointer to the mapped buffer memory, or a null pointer if an error occurred.
         */
        [[nodiscard]]
        auto map(AccessMode access) const -> void *;

        /// Map a range within the buffer to the host address space.
        /**
         * Wraps glMapBufferRange.
         * @param offset byte offset into the buffer.
         * @param length in bytes of the region to map.
         * @param access access policy flags.
         * @return a valid pointer to the mapped buffer memory, or a null pointer if an error occurred.
         */
        [[nodiscard]]
        auto mapRange(GLintptr offset, GLsizeiptr length, AccessFlags access) const -> void *;

        /// Unmap this buffer.
        /**
         * Wraps glUnmapBuffer.
         *
         * This invalidates the pointer returned by map() and map().
         */
        void unmap() const;
    };

    /// Specifies a byte offset into a buffer object.
    struct BufferOffset {
        Buffer buffer {};
        GLintptr offset {0};

        /// Construct a null offset: a zero byte offset into the zero-named buffer.
        BufferOffset() = default;

        /// Construct an instance that specifies a @p size byte offset into the given buffer.
        BufferOffset(Buffer b, GLintptr o) : buffer(b), offset(o) {}

        /// Write @p size bytes to the buffer, starting at offset .
        void write(GLsizeiptr size, const void *data) const;

        /// Read @p size bytes from the buffer, starting at offset .
        void read(GLsizeiptr size, void *data) const;

        /// Map @p length bytes of device memory to the host address space, starting at offset .
        [[nodiscard]]
        auto map(GLsizeiptr length, Buffer::AccessFlags access) const -> void *;
    };

    /// Specifies a memory range within a buffer object.
    struct BufferRange : BufferOffset {
        GLsizeiptr size {0};

        /// Construct a null range; a zero byte range within the zero-named buffer.
        BufferRange() = default;

        /// Construct a @p s byte range starting at the offset specified in @p s.
        BufferRange(BufferOffset o, GLsizeiptr s) : BufferOffset(o), size(s) {}

        /// Construct a new range.
        BufferRange(Buffer b, GLintptr o, GLsizeiptr s) : BufferOffset(b, o), size(s) {}

        /// Write to this GPU memory range.
        void write(const void *data) const;

        /// Read from this GPU memory range.
        void read(void *data) const;

        /// Map this memory range to the host memory address space.
        [[nodiscard]]
        auto map(Buffer::AccessFlags access) const -> void *;
    };

    auto operator|(Buffer::AccessFlags l, Buffer::AccessFlags r) -> Buffer::AccessFlags;

    auto operator&(Buffer::AccessFlags l, Buffer::AccessFlags r) -> Buffer::AccessFlags;

    auto operator|(Buffer::StorageFlags l, Buffer::StorageFlags r) -> Buffer::StorageFlags;

    auto operator&(Buffer::StorageFlags l, Buffer::StorageFlags r) -> Buffer::StorageFlags;


} // glutils

#endif //GLUTILS_BUFFER_HPP
