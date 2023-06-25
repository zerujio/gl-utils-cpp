#ifndef PROCEDURALPLACEMENTLIB_TEXTURE_HPP
#define PROCEDURALPLACEMENTLIB_TEXTURE_HPP

#include "handle.hpp"
#include "object.hpp"

namespace GL {

class TextureHandle : public Handle
{
    using Handle::Handle;
public:
    enum class Type : GLenum
    {
        _1d = 0x0DE0,
        _2d = 0x0DE1,
        _3d = 0x806F,
        _1d_array = 0x8C18,
        _2d_array = 0x8C1A,
        rectangle = 0x84F5,
        cube_map = 0x8513,
        buffer = 0x8C2A,
        _2d_multisample = 0x9100,
        _2d_multisample_array = 0x9102
    };

    static TextureHandle create(Type type);

    static void destroy(TextureHandle handle);

    enum class SizedInternalFormat : GLenum
    {
        r8 = 0x8229,
        r8_snorm = 0x8F94,
        r16 = 0x822A,
        r16_snorm = 0x8F98,
        rg8 = 0x822B,
        rg8_snorm = 0x8F95,
        rg16 = 0x822C,
        rg16_snorm = 0x8F99,
        r3_g3_b2 = 0x2A10,
        rgb4 = 0x804F,
        rgb5 = 0x8050,
        rgb8 = 0x8051,
        rgb8_snorm = 0x8F96,
        rgb0 = 0x8052,
        rgb12 = 0x8053,
        rgb16_snorm = 0x8F9A,
        rgba2 = 0x8055,
        rgba4 = 0x8056,
        rgb5_a1 = 0x8057,
        rgba8 = 0x8058,
        rgba8_snorm = 0x8F97,
        rgb10_a2 = 0x8059,
        rgb10_a2ui = 0x906F,
        rgba12 = 0x8D70,
        rgba16 = 0x805B,
        srgb8 = 0x8C41,
        srgb8_alpha8 = 0x8C43,
        r16f = 0x822D,
        rg16f = 0x822F,
        rgb16f = 0x881B,
        rgba16f = 0x881A,
        r32f = 0x822E,
        rg32f = 0x8230,
        rgb32f = 0x8815,
        rgba32f = 0x8814,
        r11f_g11f_b10f = 0x8C3A,
        rgb9_e5 = 0x8C3D,
        r8i = 0x8231,
        r8ui = 0x8232,
        r16i = 0x8233,
        r16ui = 0x8234,
        r32i = 0x8235,
        r32ui = 0x8236,
        rg8i = 0x8237,
        rg8ui = 0x8238,
        rg16i = 0x8239,
        rg16ui = 0x823A,
        rg32i = 0x823B,
        rg32ui = 0x823C,
        rgb8i = 0x8D8F,
        rgb8ui = 0x8D7D,
        rgb16i = 0x8D89,
        rgb16ui = 0x8D77,
        rgb32i = 0x8D83,
        rgb32ui = 0x8D71,
        rgba8i = 0x8D8E,
        rgba8ui = 0x8D7C,
        rgba16i = 0x8D88,
        rgba16ui = 0x8D76,
        rgba32i = 0x8D76,
        rgba32ui = 0x8D70,
    };

    /// glTextureStorage2D — simultaneously specify storage for all levels of a two-dimensional or one-dimensional array texture
    void setStorage2D(GLsizei levels, SizedInternalFormat internal_format, GLsizei width, GLsizei height) const;

    enum class BaseInternalFormat : GLenum
    {
        red = 0x1903,
        rg = 0x8227,
        rgb = 0x1907,
        rgba = 0x1908,
    };

    enum class DataFormat : GLenum
    {
        red = GLenum(BaseInternalFormat::red),
        rg = GLenum(BaseInternalFormat::rg),
        rgb = GLenum(BaseInternalFormat::rgb),
        bgr = 0x80E0,
        rgba = GLenum(BaseInternalFormat::rgba),
        bgra = 0x80E1,
        depth_component = 0x1902,
        stencil_index = 0x1901
    };

    enum class DataType : GLenum
    {
        ubyte = 0x1401,
        _byte = 0x1400,
        ushort = 0x1403,
        _short = 0x1402,
        uint = 0x1405,
        _int = 0x1404,
        half_float = 0x140B,
        _float = 0x1406,
        ubyte_3_3_2 = 0x8032,
        ubyte_2_3_3_rev = 0x8362,
        ushort_5_6_5 = 0x8363,
        ushort_5_6_5_rev = 0x8364,
        ushort_4_4_4_4 = 0x8033,
        ushort_4_4_4_4_rev = 0x8365,
        ushort_5_5_5_1 = 0x8034,
        ushort_1_5_5_5_rev = 0x8366,
        uint_8_8_8_8 = 0x8035,
        uint_8_8_8_8_rev = 0x8367,
        uint_10_10_10_2 = 0x8036,
        uint_2_10_10_10_rev = 0x8368
    };

    /// glTextureSubImage2D — specify a two-dimensional texture subimage.
    void updateImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, DataFormat format,
                       DataType type, const void *pixel_data) const;

    void generateMipmap() const;

    static void bindTextureUnit(GLuint texture_unit_index, TextureHandle texture);
};

using Texture = Object<TextureHandle>;

} // GL

#endif //PROCEDURALPLACEMENTLIB_TEXTURE_HPP
