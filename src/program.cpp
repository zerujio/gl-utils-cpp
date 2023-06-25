#include "glutils/program.hpp"
#include "glutils/gl.hpp"

#include "glm/gtc/type_ptr.hpp"

namespace GL {

auto ProgramHandle::create() -> ProgramHandle
{
    return ProgramHandle{glCreateProgram()};
}

void ProgramHandle::destroy(ProgramHandle program)
{
    glDeleteProgram(program.getName());
}

auto ProgramHandle::getParameter(ProgramHandle::Parameter parameter) const -> GLint
{
    GLint value;
    glGetProgramiv(getName(), static_cast<GLenum>(parameter), &value);
    return value;
}

void ProgramHandle::getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const
{
    glGetProgramInfoLog(getName(), max_length, length, info_log);
}

auto ProgramHandle::getInterface(GLenum interface, GLenum parameter) const -> GLint
{
    GLint value;
    glGetProgramInterfaceiv(getName(), interface, parameter, &value);
    return value;
}

void ProgramHandle::getResource(Interface interface, GLuint index, GLsizei prop_count, const GLenum *props,
                                GLsizei buf_size, GLsizei *length, GLint *params) const
{
    glGetProgramResourceiv(getName(), static_cast<::GLenum>(interface), index, prop_count, props, buf_size, length,
                           params);
}

auto ProgramHandle::getResourceLocation(Interface interface, const char *name) const -> GLint
{
    return glGetProgramResourceLocation(getName(), static_cast<GLenum>(interface), name);
}

auto ProgramHandle::getResourceIndex(Interface interface, const char *name) const -> GLuint
{
    return glGetProgramResourceIndex(getName(), static_cast<GLenum>(interface), name);
}

auto ProgramHandle::getResourceLocationIndex(Interface interface, const char *name) const -> GLint
{
    return glGetProgramResourceLocationIndex(getName(), static_cast<GLenum>(interface), name);
}

auto
ProgramHandle::getResourceName(Interface interface, GLuint index, GLsizei buf_size, GLsizei *length, char *name) const
{
    glGetProgramResourceName(getName(), static_cast<GLenum>(interface), index, buf_size, length, name);
}

void ProgramHandle::use() const
{
    glUseProgram(getName());
}

void ProgramHandle::setUniformBlockBinding(GLuint index, GLuint binding) const
{
    glUniformBlockBinding(getName(), index, binding);
}

void ProgramHandle::setShaderStorageBlockBinding(GLuint block_index, GLuint binding) const
{
    glShaderStorageBlockBinding(getName(), block_index, binding);
}

void ProgramHandle::link() const
{
    glLinkProgram(getName());
}

void ProgramHandle::attachShader(ShaderHandle shader) const
{
    glAttachShader(getName(), shader.getName());
}

void ProgramHandle::detachShader(ShaderHandle shader) const
{
    glDetachShader(getName(), shader.getName());
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
    glBindAttribLocation(m_name, index, name);
}

#define GLUTILS_PROGRAM_UNIFORM(N, SUFFIX) glProgramUniform##N##SUFFIX
#define GLUTILS_PROGRAM_UNIFORM_FUNCTIONS_DEFINITION(TYPE, TYPE_SUFFIX) \
    template<> const Program::GLProgramUniformFunctions<TYPE> ProgramHandle::s_program_uniform_functions<TYPE> \
    {                                                                   \
        GLUTILS_PROGRAM_UNIFORM(1, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(2, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(3, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(4, TYPE_SUFFIX)                         \
    };

#define GLUTILS_PROGRAM_UNIFORM_V(N, SUFFIX) glProgramUniform##N##SUFFIX##v
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

#define GLUTILS_PROGRAM_UNIFORM_MATRIX(DIM, SUFFIX) glProgramUniformMatrix##DIM##SUFFIX##v
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