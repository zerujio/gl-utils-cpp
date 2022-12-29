#include "glutils/program.hpp"
#include "glutils/gl.hpp"

#include "glm/gtc/type_ptr.hpp"

namespace GL {

auto ProgramHandle::create() -> ProgramHandle
{
    return ProgramHandle{gl.CreateProgram()};
}

void ProgramHandle::destroy(ProgramHandle program)
{
    gl.DeleteProgram(program.getName());
}

auto ProgramHandle::getParameter(ProgramHandle::Parameter parameter) const -> GLint
{
    GLint value;
    gl.GetProgramiv(getName(), static_cast<GLenum>(parameter), &value);
    return value;
}

void ProgramHandle::getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const
{
    gl.GetProgramInfoLog(getName(), max_length, length, info_log);
}

auto ProgramHandle::getInterface(GLenum interface, GLenum parameter) const -> GLint
{
    GLint value;
    gl.GetProgramInterfaceiv(getName(), interface, parameter, &value);
    return value;
}

void ProgramHandle::getResource(GLenum interface, GLuint index, GLsizei prop_count, const GLenum *props,
                                GLsizei buf_size, GLsizei *length, GLint *params) const
{
    gl.GetProgramResourceiv(getName(), interface, index, prop_count, props, buf_size, length, params);
}

auto ProgramHandle::getResourceLocation(Interface interface, const char *name) const -> GLint
{
    return gl.GetProgramResourceLocation(getName(), static_cast<GLenum>(interface), name);
}

auto ProgramHandle::getResourceIndex(Interface interface, const char *name) const -> GLuint
{
    return gl.GetProgramResourceIndex(getName(), static_cast<GLenum>(interface), name);
}

auto ProgramHandle::getResourceLocationIndex(Interface interface, const char *name) const -> GLint
{
    return gl.GetProgramResourceLocationIndex(getName(), static_cast<GLenum>(interface), name);
}

auto
ProgramHandle::getResourceName(Interface interface, GLuint index, GLsizei buf_size, GLsizei *length, char *name) const
{
    gl.GetProgramResourceName(getName(), static_cast<GLenum>(interface), index, buf_size, length, name);
}

void ProgramHandle::use() const
{
    gl.UseProgram(getName());
}

void ProgramHandle::setUniformBlockBinding(GLuint index, GLuint binding) const
{
    gl.UniformBlockBinding(getName(), index, binding);
}

void ProgramHandle::setShaderStorageBlockBinding(GLuint block_index, GLuint binding) const
{
    gl.ShaderStorageBlockBinding(getName(), block_index, binding);
}

void ProgramHandle::link() const
{
    gl.LinkProgram(getName());
}

void ProgramHandle::attachShader(ShaderHandle shader) const
{
    gl.AttachShader(getName(), shader.getName());
}

void ProgramHandle::detachShader(ShaderHandle shader) const
{
    gl.DetachShader(getName(), shader.getName());
}

std::string ProgramHandle::getInfoLog() const
{
    const auto len = getParameter(ProgramHandle::Parameter::info_log_length);

    if (len <= 0)
        return {};

    std::string log(len, '\n');
    getInfoLog(len, nullptr, log.data());

    return log;
}

void ProgramHandle::bindAttribLocation(GLuint index, const char *name) const
{
    gl.BindAttribLocation(m_name, index, name);
}

auto ProgramHandle::getGL() -> ProgramHandle::GLContext *
{
    return &gl;
}

#define GLUTILS_GL_CONTEXT_PTR_TO_MEMBER_FUNC(MEMBER) &GladGLContext::MEMBER
#define GLUTILS_PROGRAM_UNIFORM(N, SUFFIX) GLUTILS_GL_CONTEXT_PTR_TO_MEMBER_FUNC(ProgramUniform##N##SUFFIX)
#define GLUTILS_PROGRAM_UNIFORM_FUNCTIONS_DEFINITION(TYPE, TYPE_SUFFIX) \
    template<> const Program::GLProgramUniformFunctions<TYPE> ProgramHandle::s_program_uniform_functions<TYPE> \
    {                                                                   \
        GLUTILS_PROGRAM_UNIFORM(1, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(2, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(3, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(4, TYPE_SUFFIX)                         \
    };

#define GLUTILS_PROGRAM_UNIFORM_V(N, SUFFIX) GLUTILS_GL_CONTEXT_PTR_TO_MEMBER_FUNC(ProgramUniform##N##SUFFIX##v)
#define GLUTILS_PROGRAM_UNIFORM_V_FUNCTIONS_DEFINITION(TYPE, SUFFIX) \
    template<> const Program::GLProgramUniformvFunctions<TYPE> ProgramHandle::s_program_uniform_v_functions<TYPE> \
    {                                                                \
        GLUTILS_PROGRAM_UNIFORM_V(1, SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM_V(2, SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM_V(3, SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM_V(4, SUFFIX)                         \
    };

#define GLUTILS_PROGRAM_UNIFORM_DEFINITIONS(TYPE, SUFFIX) \
    GLUTILS_PROGRAM_UNIFORM_FUNCTIONS_DEFINITION(TYPE, SUFFIX) \
    GLUTILS_PROGRAM_UNIFORM_V_FUNCTIONS_DEFINITION(TYPE, SUFFIX)

GLUTILS_PROGRAM_UNIFORM_DEFINITIONS(float, f)
GLUTILS_PROGRAM_UNIFORM_DEFINITIONS(double, d)
GLUTILS_PROGRAM_UNIFORM_DEFINITIONS(int, i)
GLUTILS_PROGRAM_UNIFORM_DEFINITIONS(unsigned int, ui)

#define GLUTILS_PROGRAM_UNIFORM_MATRIX(DIM, SUFFIX) GLUTILS_GL_CONTEXT_PTR_TO_MEMBER_FUNC(ProgramUniformMatrix##DIM##SUFFIX##v)
#define GLUTILS_PROGRAM_UNIFORM_MATRIX_FUNCTIONS_DEFINITION(TYPE, SUFFIX) \
    template<> const ProgramHandle::GLProgramUniformMatrixFunctions<TYPE> ProgramHandle::s_program_uniform_matrix_functions<TYPE>  = \
    {                                                                     \
        {                                                                 \
            {                                                             \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(2,   SUFFIX),              \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(2x3, SUFFIX),              \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(2x4, SUFFIX)               \
            }, {                                                          \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(3x2, SUFFIX),              \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(3,   SUFFIX),              \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(3x4, SUFFIX)               \
            }, {                                                          \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(4x2, SUFFIX),              \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(4x3, SUFFIX),              \
                GLUTILS_PROGRAM_UNIFORM_MATRIX(4,   SUFFIX)               \
            }                                                             \
        }                                                                 \
    };

GLUTILS_PROGRAM_UNIFORM_MATRIX_FUNCTIONS_DEFINITION(float, f)
GLUTILS_PROGRAM_UNIFORM_MATRIX_FUNCTIONS_DEFINITION(double, d)

} // GL