#ifndef GLUTILS_PROXY_HPP
#define GLUTILS_PROXY_HPP

#include "gl.h"
#include "error.hpp"

#include <sstream>

namespace glutils {

    /// Manages access and lifetime of an OpenGL object in RAII style.
    /**
     * @tparam Create A wrapper for the constructor function
     * @tparam Destroy A wrapper for the destructor function
     * @tparam Validate A wrapper for the validation function
     */
    template<auto Create, auto Destroy, auto Validate>
    class Proxy {
    public:
        /// Create and take ownership of an new instance.
        template<class... Args>
        Proxy(Args... args) : m_name(Create(args...)) {}

        /// Destroy the managed object.
        ~Proxy() {
            Destroy(m_name);
        }

        /// Take ownership of an existing object.
        Proxy(GLuint name) : m_name(name) {
            if (!validate()) {
                std::ostringstream msg {"Invalid object name: "};
                msg << name;
                throw GLError(msg.str());
            }
        }

        /// Move constructor
        /**
         *
         * @param other Another object proxy. Will be left managing no object.
         */
        Proxy(Proxy && other) : m_name(other.m_name) {
            other.m_name = 0;
        }

        /// Move assignment operator.
        /**
         * The currently managed object will be deleted.
         * @param other Another proxy. Will be left managing no object.
         * @return this object.
         */
        Proxy& operator=(Proxy && other) noexcept {
            Destroy(m_name);
            m_name = other.m_name;
            other.m_name = 0;

            return *this;
        }

        /// Checks if this proxy references a valid object.
        [[nodiscard]] bool validate() const {
            return Validate(m_name);
        }

        /// Get the integer identifier of the managed object.
        [[nodiscard]] GLuint getName() const {
            return m_name;
        }

    private:
        GLuint m_name;
    };

} // glutils

#endif //GLUTILS_PROXY_HPP
