#ifndef GLUTILS_VERTEX_ATTRIB_ENUMS_HPP
#define GLUTILS_VERTEX_ATTRIB_ENUMS_HPP

#include "gl_types.hpp"

#include <stdexcept>

namespace GL {

enum class VertexAttributeBaseType : GLenum
{
    _byte = 0x1400,
    _ubyte = 0x1401,
    _short = 0x1402,
    _ushort = 0x1403,
    _int = 0x1404,
    _uint = 0x1405,
    _fixed = 0x140C,
    _float = 0x1406,
    _half_float = 0x140B,
    _double = 0x140A,
    int_2_10_10_10_rev = 0x8D9F,
    uint_2_10_10_10_rev = 0x8368,
    uint_10f_11f_11f_rev = 0x8C3B
};

enum class VertexAttributeLength : GLenum
{
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4
};
}

#endif //GLUTILS_VERTEX_ATTRIB_ENUMS_HPP
