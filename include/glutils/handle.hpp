#ifndef SIMPLERENDERER_HANDLE_HPP
#define SIMPLERENDERER_HANDLE_HPP

#include "gl.h"

namespace glutils {

    using GLCreateProc = void (*) (GLsizei, GLuint *);
    using GLDeleteProc = void (*) (GLsizei, const GLuint *);
    using GLIsProc = GLboolean (*) (GLuint);

    /// A wrapper around an OpenGL integer name providing an object-oriented interface.
    template <GLIsProc GladGLContext::* Is>
    class BaseHandle {
    public:
        BaseHandle() = default;

        /// Check if the handle references a valid object.
        [[nodiscard]]
        auto validate() const -> bool
        {
            return (gl.*Is)(m_name);
        }

        /// Retrieve the underlying integer name.
        [[nodiscard]]
        auto getName() const -> GLuint
        {
            return m_name;
        }

    protected:
        explicit BaseHandle(GLuint name) : m_name(name) {}

    private:
        GLuint m_name {0};
    };

    template <class HandleType,
            GLCreateProc GladGLContext::* Create,
            GLDeleteProc GladGLContext::* Delete,
            GLIsProc GladGLContext::* Is>
    class Handle : public BaseHandle<Is>
    {
    public:
        /// Create a new OpenGL object and return a handle to it.
        [[nodiscard]]
        static auto create() -> HandleType
        {
            HandleType handle;
            (gl.*Create)(1, reinterpret_cast<GLuint *>(&handle));
            return handle;
        }

        /// Destroy the OpenGL object referenced by the @p handle.
        static void destroy(Handle handle)
        {
            (gl.*Delete)(1, reinterpret_cast<const GLuint *>(&handle));
        }
    };

} // glutils

#endif //SIMPLERENDERER_HANDLE_HPP
