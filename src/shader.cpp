#include "glutils/shader.hpp"
#include "glutils/gl.hpp"

namespace GL {

auto ShaderHandle::create(ShaderHandle::Type type) -> ShaderHandle
{
    return ShaderHandle{glCreateShader(static_cast<GLenum>(type))};
}

void ShaderHandle::destroy(ShaderHandle shader)
{
    glDeleteShader(shader.getName());
}

void ShaderHandle::setSource(GLsizei count, const GLchar **string, const GLint *length) const
{
    glShaderSource(getName(), count, string, length);
}

void ShaderHandle::compile() const
{
    glCompileShader(getName());
}

auto ShaderHandle::getParameter(ShaderHandle::Parameter parameter) const -> GLint
{
    GLint value;
    glGetShaderiv(getName(), static_cast<GLenum>(parameter), &value);
    return value;
}

void ShaderHandle::getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const
{
    glGetShaderInfoLog(getName(), max_length, length, info_log);
}

std::string ShaderHandle::getInfoLog() const
{
    const auto log_length = getParameter(Parameter::info_log_length);

    if (log_length <= 0)
        return {};

    std::string log(log_length, '\0');
    getInfoLog(log_length, nullptr, log.data());

    return log;
}


} // GL