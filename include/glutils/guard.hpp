#ifndef GLUTILS_GUARD_HPP
#define GLUTILS_GUARD_HPP

#include "gl.h"

namespace glutils {

    /// Manages the lifetime of an OpenGL object in RAII style.
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
        ~Guard() {
            HandleType::destroy(m_handle);
        }

        /// Move constructor.
        /**
         * @param other Another object guard. Will be left managing no object.
         */
        Guard(Guard && other) : m_handle(other.m_handle) {
            other.m_handle = HandleType();
        }

        /// Move assignment operator.
        /**
         * The currently managed object will be deleted.
         * @param other Another object guard. Will be left managing no object.
         * @return this object.
         */
        Guard& operator=(Guard && other) noexcept {
            HandleType::destroy(m_handle);
            m_handle = other.m_handle;
            other.m_handle = HandleType();
            return *this;
        }

    private:
        HandleType m_handle;
    };

} // glutils

#endif //GLUTILS_GUARD_HPP
