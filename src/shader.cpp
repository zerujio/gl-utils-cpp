#include "glutils/shader.hpp"
#include "glutils/gl.hpp"

namespace glutils {

    auto Shader::create(Shader::Type type) -> Shader
    {
        return Shader{gl.CreateShader(static_cast<GLenum>(type))};
    }

    void Shader::destroy(Shader shader)
    {
        gl.DeleteShader(shader.getName());
    }

    void Shader::setSource(GLsizei count, const GLchar **string, const GLint *length) const
    {
        gl.ShaderSource(getName(), count, string, length);
    }

    void Shader::compile() const
    {
        gl.CompileShader(getName());
    }

    auto Shader::getParameter(Shader::Parameter parameter) const -> GLint
    {
        GLint value;
        gl.GetShaderiv(getName(), static_cast<GLenum>(parameter), &value);
        return value;
    }

    void Shader::getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const
    {
        gl.GetShaderInfoLog(getName(), max_length, length, info_log);
    }


} // glutils