#ifndef PROCEDURALPLACEMENTLIB_OBJECT_HPP
#define PROCEDURALPLACEMENTLIB_OBJECT_HPP

#include "gl_types.hpp"

namespace GL {

/**
 * @brief Wraps an OpenGL object in object-oriented interface.
 * @tparam HandleType Base handle type of the underlying OpenGL object.
 */
template<typename HandleType>
class Object final : public HandleType
{
public:
    /**
     * @brief Create a new object using HandleType::create()
     * @tparam Args Argument types of the object constructor.
     * @param args Values to pass to the object constructor.
     */
    template<typename ... Args>
    explicit Object(Args... args) : HandleType(HandleType::create(args...))
    {}

    /// Take ownership of the object referred to by @p handle. There should be at most one Object instance for each GL object.
    explicit Object(HandleType handle) : HandleType(handle)
    {}

    /// Destroy the owned object using HandleType::destroy()
    ~Object()
    {
        if (*this)
            HandleType::destroy(*this);
    }

    /// Take ownership of the object held by @p other, which will be left holding no object.
    Object(Object &&other) noexcept: HandleType(other)
    {
        HandleType &other_handle = other;
        other_handle = HandleType();
    }

    /// Take ownership of the object @p handle refers to and destroy the currently owned one.
    Object &operator=(HandleType handle) noexcept
    {
        HandleType::destroy(*this);
        HandleType &this_handle = *this;
        this_handle = handle;

        return *this;
    }

    /// Take ownership of the object held by @p other and destroy the one owned by *this.
    Object &operator=(Object &&other) noexcept
    {
        if (*this)
            HandleType::destroy(*this);

        HandleType &this_handle = *this;
        HandleType &other_handle = other;
        this_handle = other_handle;
        other_handle = HandleType();

        return *this;
    }
};

} // GL

#endif //PROCEDURALPLACEMENTLIB_OBJECT_HPP
