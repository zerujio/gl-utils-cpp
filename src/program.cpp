#include "glutils/program.hpp"
#include "glutils/gl.hpp"

#include "glm/gtc/type_ptr.hpp"

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

    auto Program::getResourceLocation(Interface interface, const char *name) const -> GLint
    {
        return gl.GetProgramResourceLocation(getName(), static_cast<GLenum>(interface), name);
    }

    auto Program::getResourceIndex(Interface interface, const char *name) const -> GLuint
    {
        return gl.GetProgramResourceIndex(getName(), static_cast<GLenum>(interface), name);
    }

    auto Program::getResourceLocationIndex(Interface interface, const char *name) const -> GLint
    {
        return gl.GetProgramResourceLocationIndex(getName(), static_cast<GLenum>(interface), name);
    }

    auto Program::getResourceName(Interface interface, GLuint index, GLsizei buf_size, GLsizei *length, char *name) const
    {
        gl.GetProgramResourceName(getName(), static_cast<GLenum>(interface), index, buf_size, length, name);
    }

    void Program::use() const
    {
        gl.UseProgram(getName());
    }

    void Program::setUniformBlockBinding(GLuint index, GLuint binding) const
    {
        gl.UniformBlockBinding(getName(), index, binding);
    }

    void Program::setShaderStorageBlockBinding(GLuint block_index, GLuint binding) const
    {
        gl.ShaderStorageBlockBinding(getName(), block_index, binding);
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

    std::string Program::getInfoLog() const
    {
        const auto len = getParameter(Program::Parameter::info_log_length);

        if (len <= 0)
            return {};

        std::string log(len, '\n');
        getInfoLog(len, nullptr, log.data());

        return log;
    }

    void Program::bindAttribLocation(GLuint index, const char *name) const
    {
        gl.BindAttribLocation(m_name, index, name);
    }

    auto Program::getGL() -> Program::GLContext *
    {
        return &gl;
    }

#define GLUTILS_GL_CONTEXT_PTR_TO_MEMBER_FUNC(MEMBER) &GladGLContext::MEMBER
#define GLUTILS_PROGRAM_UNIFORM(N, SUFFIX) GLUTILS_GL_CONTEXT_PTR_TO_MEMBER_FUNC(ProgramUniform##N##SUFFIX)
#define GLUTILS_PROGRAM_UNIFORM_FUNCTIONS_DEFINITION(TYPE, TYPE_SUFFIX) \
    template<> const Program::GLProgramUniformFunctions<TYPE> Program::s_program_uniform_functions<TYPE> \
    {                                                                   \
        GLUTILS_PROGRAM_UNIFORM(1, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(2, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(3, TYPE_SUFFIX),                        \
        GLUTILS_PROGRAM_UNIFORM(4, TYPE_SUFFIX)                         \
    };

#define GLUTILS_PROGRAM_UNIFORM_V(N, SUFFIX) GLUTILS_GL_CONTEXT_PTR_TO_MEMBER_FUNC(ProgramUniform##N##SUFFIX##v)
#define GLUTILS_PROGRAM_UNIFORM_V_FUNCTIONS_DEFINITION(TYPE, SUFFIX) \
    template<> const Program::GLProgramUniformvFunctions<TYPE> Program::s_program_uniform_v_functions<TYPE> \
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
    template<> const Program::GLProgramUniformMatrixFunctions<TYPE> Program::s_program_uniform_matrix_functions<TYPE>  = \
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

} // glutils