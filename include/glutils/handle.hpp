#ifndef SIMPLERENDERER_HANDLE_HPP
#define SIMPLERENDERER_HANDLE_HPP

#include "gl_types.hpp"

namespace GL {

/// A wrapper around an OpenGL integer name providing an object-oriented interface.
class Handle
{
public:
    constexpr Handle() = default;

    constexpr explicit Handle(GLuint name) : m_name(name)
    {}

    /// Retrieve the underlying integer name.
    [[nodiscard]]
    constexpr auto getName() const -> GLuint
    {
        return m_name;
    }

    // Checks if the integer name is zero, which indicates a null object.
    [[nodiscard]] bool isZero() const
    { return m_name == 0; }

    [[nodiscard]] explicit operator bool() const
    { return !isZero(); }

protected:
    GLuint m_name{0};
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
