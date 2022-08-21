#include "glutils/program.hpp"

namespace glutils {

    auto Program::create() -> Program
    {
        return Program{gl.CreateProgram()};
    }

    void Program::destroy(Program program)
    {
        gl.DeleteProgram(program.getName());
    }

    auto Program::getParameter(Program::Parameter parameter) const -> GLint
    {
        GLint value;
        gl.GetProgramiv(getName(), static_cast<GLenum>(parameter), &value);
        return value;
    }

    void Program::getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const
    {
        gl.GetProgramInfoLog(getName(), max_length, length, info_log);
    }

    auto Program::getInterface(GLenum interface, GLenum parameter) const -> GLint
    {
        GLint value;
        gl.GetProgramInterfaceiv(getName(), interface, parameter, &value);
        return value;
    }

    void Program::getResource(GLenum interface, GLuint index, GLsizei prop_count, const GLenum *props,
                                         GLsizei buf_size, GLsizei *length, GLint *params) const
    {
        gl.GetProgramResourceiv(getName(), interface, index, prop_count, props, buf_size, length, params);
    }

    auto Program::getResourceLocation(GLenum interface, const char *name) const -> GLint
    {
        return gl.GetProgramResourceLocation(getName(), interface, name);
    }

    auto Program::getResourceIndex(GLenum interface, const char *name) const -> GLuint
    {
        return gl.GetProgramResourceIndex(getName(), interface, name);
    }

    auto Program::getResourceLocationIndex(GLenum interface, const char *name) const -> GLint
    {
        return gl.GetProgramResourceLocationIndex(getName(), interface, name);
    }

    auto Program::getResourceName(GLenum interface, GLuint index, GLsizei buf_size, GLsizei *length, char *name) const
    {
        gl.GetProgramResourceName(getName(), interface, index, buf_size, length, name);
    }

    void Program::use() const
    {
        gl.UseProgram(getName());
    }

    void Program::setBlockBinding(GLuint index, GLuint binding) const
    {
        gl.UniformBlockBinding(getName(), index, binding);
    }

    void Program::link() const
    {
        gl.LinkProgram(getName());
    }

    void Program::attachShader(Shader shader) const
    {
        gl.AttachShader(getName(), shader.getName());
    }

    void Program::detachShader(Shader shader) const
    {
        gl.DetachShader(getName(), shader.getName());
    }

} // glutils