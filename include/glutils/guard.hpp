#ifndef GLUTILS_GUARD_HPP
#define GLUTILS_GUARD_HPP

#include "gl.h"

namespace glutils {

    /// Manages the lifetime of an OpenGL object in RAII style (like std::unique_ptr).
    /**
     *
     * @tparam HandleType a type that inherits from Handle.
     */
    template<class HandleType>
    class Guard {
    public:
        /// Create and take ownership of a new instance.
        template<class... Args>
        Guard(Args... args) : m_handle(HandleType::create(args...)) {}

        /// Destroy the managed object.
        ~Guard()
        {
            HandleType::destroy(m_handle);
        }

        /// Move constructor.
        /**
         * @param other Another object guard. Will be left managing no object.
         */
        Guard(Guard && other)  noexcept : m_handle(other.release()) {}

        /// Move assignment operator.
        /**
         * The currently managed object will be deleted.
         * @param other Another object guard. Will be left managing no object.
         * @return this object.
         */
        auto operator=(Guard && other) noexcept -> Guard&
        {
            reset(other.release());
            return *this;
        }

        /// Get handle to object.
        auto getHandle() const -> HandleType {return m_handle;}

        /// Same as getHandle()
        auto operator*() const -> HandleType {return m_handle;}

        /// Access handle.
        auto operator->() const -> const HandleType * {return &m_handle;}

        /// Release ownership of the managed object.
        /**
         * The object is not destroyed.
         * @return A handle to the object.
         */
        auto release() -> HandleType
        {
            auto copy = m_handle;
            m_handle = HandleType();
            return copy;
        }

        /// Change the managed object.
        /**
         * The current object will be destroyed.
         * @param new_handle A (possibly zero) handle.
         */
        void reset(HandleType new_handle)
        {
            HandleType::destroy(m_handle);
            m_handle = new_handle;
        }

    private:
        HandleType m_handle;
    };

} // glutils

#endif //GLUTILS_GUARD_HPP
