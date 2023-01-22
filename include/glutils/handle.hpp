#ifndef SIMPLERENDERER_HANDLE_HPP
#define SIMPLERENDERER_HANDLE_HPP

#include "gl_types.hpp"

struct GladGLContext;

namespace GL {

/// A wrapper around an OpenGL integer name providing an object-oriented interface.
class Handle {
public:
    constexpr Handle() = default;

    constexpr explicit Handle(GLuint name) : m_name(name) {}

    /// Retrieve the underlying integer name.
    [[nodiscard]]
    constexpr auto getName() const -> GLuint
    {
        return m_name;
    }

protected:
    GLuint m_name {0};
};

constexpr bool operator==(const Handle &lhs, const Handle &rhs)
{
    return lhs.getName() == rhs.getName();
}

constexpr bool operator!=(const Handle &lhs, const Handle &rhs)
{
    return !(rhs == lhs);
}

constexpr bool operator<(const Handle &lhs, const Handle &rhs)
{
    return lhs.getName() < rhs.getName();
}

constexpr bool operator>(const Handle &lhs, const Handle &rhs)
{
    return rhs < lhs;
}

constexpr bool operator<=(const Handle &lhs, const Handle &rhs)
{
    return !(rhs < lhs);
}

constexpr bool operator>=(const Handle &lhs, const Handle &rhs)
{
    return !(lhs < rhs);
}

} // GL

#endif //SIMPLERENDERER_HANDLE_HPP
