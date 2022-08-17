#ifndef SIMPLERENDERER_HANDLE_HPP
#define SIMPLERENDERER_HANDLE_HPP

#include "gl.h"

namespace glutils {

    /// A wrapper around an OpenGL integer name providing an object-oriented interface.
    template <auto Create, auto Destroy, auto Validate>
    class Handle {
    public:

        /// A handle that references the zero object (i.e. a null pointer).
        Handle() = default;

        /// Create a new OpenGL object and return a handle to it.
        template <class... Args>
        static Handle create(Args... args) {
            return Create(args...);
        }

        /// Destroy the OpenGL object referenced by the @p handle.
        static void destroy(Handle handle) {
            Destroy(m_name);
        }

        /// Check if the handle references a valid object.
        [[nodiscard]] bool validate() const {
            return Validate(m_name);
        }

        /// Retrieve the underlying integer name.
        [[nodiscard]] GLuint getName() const {
            return m_name;
        }

    private:
        Handle(GLuint name) : m_name(name) {}

        GLuint m_name {0};
    };

} // glutils

#endif //SIMPLERENDERER_HANDLE_HPP
