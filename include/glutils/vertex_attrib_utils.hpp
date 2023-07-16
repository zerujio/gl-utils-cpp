#ifndef PROCEDURALPLACEMENTLIB_VERTEX_ATTRIB_UTILS_HPP
#define PROCEDURALPLACEMENTLIB_VERTEX_ATTRIB_UTILS_HPP

#include "vertex_attrib_enums.hpp"
#include "gl_types.hpp"

#include "glm/fwd.hpp"

namespace GL::VertexAttrib {

template<typename T> VertexAttributeType type_of;

#define DEFINE_ATTRIB(TYPE) \
template<> constexpr VertexAttributeType type_of<GL##TYPE> = VertexAttributeType::_##TYPE;

DEFINE_ATTRIB(int)
DEFINE_ATTRIB(uint)
DEFINE_ATTRIB(short)
DEFINE_ATTRIB(ushort)
DEFINE_ATTRIB(byte)
DEFINE_ATTRIB(ubyte)
DEFINE_ATTRIB(float)
DEFINE_ATTRIB(double)

#undef DEFINE_ATTRIB

template<uint L>
constexpr std::enable_if_t<1 <= L && L <= 4, VertexAttributeLength> length_of = static_cast<VertexAttributeLength>(L);

namespace impl {

template<auto V>
struct WrapValue
{
    static constexpr auto value = V;
};

template<typename T>
struct WrapType
{
    using Type = T;
};

} // namespace impl

using BaseType = VertexAttributeType;
using Length = VertexAttributeLength;

template<typename T>
struct TypeToEnum;

template<BaseType V>
struct EnumValueTo;

#define GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(TYPE) \
template<> struct TypeToEnum<GL##TYPE> : impl::WrapValue<BaseType::_##TYPE> {};\
template<> struct EnumValueTo<BaseType::_##TYPE> : impl::WrapType<GL##TYPE> {};

GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(byte)
GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(ubyte)
GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(short)
GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(ushort)
GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(int)
GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(uint)
GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(float)
GLUTILS_ATTRIB_TYPE_TO_ENUM_DEF(double)

template<typename T> constexpr BaseType TypeToEnumValue = TypeToEnum<T>::value;

template<auto V> using EnumValueToType = typename EnumValueTo<V>::Type;

template<BaseType E> constexpr auto size_of = sizeof(EnumValueToType<E>);

/// Get the size in bytes of the type associated with a given VertexAttributeBaseType enum.
constexpr unsigned int getSizeOfBaseType(VertexAttributeType type)
{
    using VA = VertexAttributeType;

    switch (type)
    {
        case VA::_byte:
            return size_of<VA::_byte>;
        case VA::_ubyte:
            return size_of<VA::_ubyte>;
        case VA::_short:
            return size_of<VA::_short>;
        case VA::_ushort:
            return size_of<VA::_ushort>;
        case VA::_int:
            return size_of<VA::_int>;
        case VA::_uint:
            return size_of<VA::_uint>;
        case VA::_fixed:
            return sizeof(GLfixed);
        case VA::_float:
            return size_of<VA::_float>;
        case VA::_half_float:
            return 2; // 16bit floating point value
        case VA::_double:
            return size_of<VA::_double>;
        case VA::int_2_10_10_10_rev:
            return sizeof(GLint);
        case VA::uint_2_10_10_10_rev:
        case VA::uint_10f_11f_11f_rev:
            return sizeof(GLuint);
        default:
            throw std::logic_error("invalid enum value");
    }
}

/// Converts an integer value to typed enum VertexAttributeLength.
constexpr VertexAttributeLength asVertexAttributeLength(GLuint length)
{
    if (length < 1 || length > 4)
        throw std::logic_error("invalid vertex attribute length; must be 1, 2, 3 or 4");

    return static_cast<VertexAttributeLength>(length);
}

/// Converts from VertexAttributeLength enum value to an integer.
constexpr GLenum toLengthValue(VertexAttributeLength length)
{ return static_cast<GLenum>(length); }

template<typename T>
struct FormatEnum final
{
    static constexpr Length length = Length::_1;
    static constexpr BaseType base_type = TypeToEnumValue<T>;
};

template<int L, typename T, glm::qualifier Q>
struct FormatEnum<glm::vec<L, T, Q>> final
{
    static constexpr Length length = asVertexAttributeLength(L);
    static constexpr BaseType base_type = TypeToEnumValue<T>;
};

} // namespace GL

#endif //PROCEDURALPLACEMENTLIB_VERTEX_ATTRIB_UTILS_HPP
