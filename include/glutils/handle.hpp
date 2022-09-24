#ifndef SIMPLERENDERER_HANDLE_HPP
#define SIMPLERENDERER_HANDLE_HPP

#include "gl_types.hpp"

struct GladGLContext;

namespace glutils {

    /// A wrapper around an OpenGL integer name providing an object-oriented interface.
    class Handle {
    public:
        Handle() = default;

        /// Retrieve the underlying integer name.
        [[nodiscard]]
        auto getName() const -> GLuint
        {
            return m_name;
        }

    protected:
        Handle(GLuint name) : m_name(name) {}
        GLuint m_name {0};
    };

} // glutils

#endif //SIMPLERENDERER_HANDLE_HPP
