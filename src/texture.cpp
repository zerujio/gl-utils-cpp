#include "glutils/texture.hpp"

#include "glutils/gl.hpp"

namespace GL {

TextureHandle TextureHandle::create(Type type)
{
    TextureHandle new_handle;
    gl.CreateTextures(GLenum(type), 1, &new_handle.m_name);
    return new_handle;
}

void TextureHandle::destroy(TextureHandle handle)
{
    gl.DeleteTextures(1, &handle.m_name);
}

void
TextureHandle::setStorage2D(GLsizei levels, TextureHandle::SizedInternalFormat internal_format, GLsizei width, GLsizei height)
const
{
    gl.TextureStorage2D(m_name, levels, GLenum(internal_format), width, height);
}

void
TextureHandle::updateImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, DataFormat format,
                             DataType type, const void *pixel_data) const
{
    gl.TextureSubImage2D(m_name, level, xoffset, yoffset, width, height, GLenum(format), GLenum(type), pixel_data);
}

void TextureHandle::generateMipmap() const
{
    gl.GenerateTextureMipmap(m_name);
}

void TextureHandle::bindTextureUnit(GLuint texture_unit_index, TextureHandle texture)
{
    gl.BindTextureUnit(texture_unit_index, texture.m_name);
}

} // GL