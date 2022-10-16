#ifndef SIMPLERENDERER_PROGRAM_HPP
#define SIMPLERENDERER_PROGRAM_HPP

#include "handle.hpp"
#include "shader.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <type_traits>

namespace glutils {

    class Program : public Handle
    {
        using Handle::Handle;
    public:
        static auto create() -> Program;

        static void destroy(Program program);

        /// Installs a program object as part of current rendering state. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
        void use() const;

        /// glLinkProgram - Links a program object. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
        void link() const;

        /// assign a binding point to an active uniform block. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniformBlockBinding.xhtml
        void setUniformBlockBinding(GLuint block_index, GLuint binding) const;

        /// glShaderStorageBlockBinding - change an active shader storage block binding. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderStorageBlockBinding.xhtml
        void setShaderStorageBlockBinding(GLuint block_index, GLuint binding) const;

        /// glBindAttribLocation — Associates a generic vertex attribute index with a named attribute variable.
        /**
         * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindAttribLocation.xhtml
         * @param index Specifies the index of the generic vertex attribute to be bound.
         * @param name Specifies a null terminated string containing the name of the vertex shader attribute variable to
         *              which index is to be bound.
         */
        void bindAttribLocation(GLuint index, const char *name) const;

        /// glAttachShader - Attaches a shader object to a program object. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
        void attachShader(Shader shader) const;

        /// glDetachShader — Detaches a shader object from a program object to which it is attached. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDetachShader.xhtml
        void detachShader(Shader shader) const;

        enum class Parameter
        {
            delete_status                   = 0x8B80,
            link_status                     = 0x8B82,
            validate_status                 = 0x8B83,
            info_log_length                 = 0x8B84,
            attached_shaders                = 0x8B85,
            active_atomic_counter_buffers   = 0x92D9,
            active_attributes               = 0x8B89,
            active_attribute_max_length     = 0x8B8A,
            active_uniforms                 = 0x8B86,
            active_uniform_blocks           = 0x8A36,
            active_uniform_block_max_name_length = 0x8A35,
            active_uniform_max_length       = 0x8B87,
            compute_work_group_size         = 0x8267,
            program_binary_length           = 0x8741,
            transform_feedback_buffer_mode  = 0x8C7F,
            transform_feedback_varyings     = 0x8C83,
            transform_feedback_varying_max_length = 0x8C76,
            geometry_vertices_out           = 0x8916,
            geometry_input_type             = 0x8917,
            geometry_output_type            = 0x8918
        };

        /// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml
        [[nodiscard]]
        auto getParameter(Parameter parameter) const -> GLint;

        /// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml
        void getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const;

        [[nodiscard]] std::string getInfoLog() const;

        enum class Interface : GLenum
        {
            uniform                     = 0x92E1,
            uniform_block               = 0x92E2,
            program_input               = 0x92E3,
            program_output              = 0x92E4,
            buffer_variable             = 0x92E5,
            shader_storage_block        = 0x92E6,

            vertex_subroutine           = 0x92E8,
            tess_control_subroutine     = 0x92E9,
            tess_evaluation_subroutine  = 0x92EA,
            geometry_subroutine         = 0x92EB,
            fragment_subroutine         = 0x92EC,
            compute_subroutine          = 0x92ED,
            vertex_subroutine_uniform   = 0x92EE,
            tess_control_subroutine_uniform     = 0x92EF,
            tess_evaluation_subroutine_uniform  = 0x92F0,
            geometry_subroutine_uniform = 0x92F1,
            fragment_subroutine_uniform = 0x92F2,
            compute_subroutine_uniform  = 0x92F3,
            transform_feedback_varying  = 0x92F4,

            transform_feedback_buffer   = 0x8C8E,

        };

        /// query a property of an interface in a program (https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInterface.xhtml)
        [[nodiscard]]
        auto getInterface(GLenum interface, GLenum parameter) const -> GLint;

        /// retrieve values for multiple properties of a single active resource within a program object. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResource.xhtml
        void getResource(GLenum interface,
                         GLuint index,
                         GLsizei prop_count,
                         const GLenum * props,
                         GLsizei buf_size,
                         GLsizei * length,
                         GLint* params) const;

        /// query the location of a named resource within a program. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceLocation.xhtml
        auto getResourceLocation(Interface interface, const char * name) const -> GLint;

        /// query the index of a named resource within a program. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceIndex.xhtml
        auto getResourceIndex(Interface interface, const char * name) const -> GLuint;

        /// query the fragment color index of a named variable within a program. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceLocationIndex.xhtml
        auto getResourceLocationIndex(Interface interface, const char * name) const -> GLint;

        /// query the name of an indexed resource within a program. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceName.xhtml
        auto getResourceName(Interface interface, GLuint index, GLsizei buf_size, GLsizei * length, char * name) const;

        /**
         * @brief glProgramUniform - Specify the value of a uniform variable for a specified program object
         * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glProgramUniform.xhtml
         */
        template<typename T>
        void setUniform(GLint location, T value) const
        {
            s_glProgramUniform<T>(m_name, location, value);
        }

        template<typename T>
        void setUniform(GLint location, GLsizei count, const T* value) const
        {
            s_glProgramUniformv<T>(m_name, location, count, value);
        }

        template<typename T>
        void setUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const T* values) const
        {
            s_glProgramUniformMatrix(m_name, location, count, transpose, values);
        }

    private:
        // glProgramUniform* helpers

        using GLContext = GladGLContext;

        static auto getGL() -> GLContext*;

        template<class R, class... Ps>
        using GLProc = R (*) (Ps...);

        template<class Return, class... Params>
        static auto s_glCall(GLProc<Return, Params...> GLContext::* proc)
        {
            return getGL().*proc;
        }

        // glProgramUniformNT
        template<class... Params> using GLProgramUniformProc = GLProc<void, GLuint, GLint, Params...>;

        template<class T>
        struct GLProgramUniformFunctions
        {
            GLProgramUniformProc<T> GLContext::* _1;
            GLProgramUniformProc<T, T> GLContext::* _2;
            GLProgramUniformProc<T, T, T> GLContext::* _3;
            GLProgramUniformProc<T, T, T, T> GLContext::* _4;
        };

        template<class T>
        static const GLProgramUniformFunctions<T> s_program_uniform_functions {};

        template<class T>
        static constexpr auto s_glProgramUniform =
                [] (GLuint program, GLint location, T value)
                {
                    s_glCall(s_program_uniform_functions<T>._1)(program, location, value);
                };

        // glUniformNTv
        template<class T> using GLProgramUniformvProc = GLProgramUniformProc<GLsizei, const T*>;

        template<class T>
        struct GLProgramUniformvFunctions
        {
            GLProgramUniformvProc<T> GLContext::* values[4];
        };

        template<class T> static const GLProgramUniformvFunctions<T> s_program_uniform_v_functions {};

        template<class T>
        static constexpr auto s_glProgramUniformv =
                [](GLuint program, GLint location, GLsizei count, const T* values)
                {
                    s_glCall(s_program_uniform_v_functions<T>[0])(program, location, count, values);
                };

        // glProgramUniformMatrix
        template<class T> using GLProgramUniformMatrixProc = GLProgramUniformProc<GLsizei, GLboolean, const T*>;

        template<class T>
        struct GLProgramUniformMatrixFunctions
        {
            GLProgramUniformMatrixProc<T> GLContext::* values[3][3];
        };

        template<class T> static const GLProgramUniformMatrixFunctions<T> s_program_uniform_matrix_functions;

        template<auto C, auto R, typename T, auto Q>
        static auto s_glProgramUniformMatrix(GLuint program, GLint location, GLsizei count, GLboolean transpose,
                                             const glm::mat<C, R, T, Q>* values)
        {
            static_assert(C > 1 && C < 5 && R > 1 && R < 5 , "C and R may only be 2, 3 or 4");

            s_glCall(s_program_uniform_matrix_functions<T>[C-2][R-2])(program, location, count, transpose,
                                                                      glm::value_ptr(values));
        }
    };

    template<> const Program::GLProgramUniformFunctions<float>          Program::s_program_uniform_functions<float>;
    template<> const Program::GLProgramUniformFunctions<double>         Program::s_program_uniform_functions<double>;
    template<> const Program::GLProgramUniformFunctions<int>            Program::s_program_uniform_functions<int>;
    template<> const Program::GLProgramUniformFunctions<unsigned int>   Program::s_program_uniform_functions<unsigned int>;

    template<> const Program::GLProgramUniformvFunctions<float>         Program::s_program_uniform_v_functions<float>;
    template<> const Program::GLProgramUniformvFunctions<double>        Program::s_program_uniform_v_functions<double>;
    template<> const Program::GLProgramUniformvFunctions<int>           Program::s_program_uniform_v_functions<int>;
    template<> const Program::GLProgramUniformvFunctions<unsigned int>  Program::s_program_uniform_v_functions<unsigned int>;

    template<> const Program::GLProgramUniformMatrixFunctions<float>    Program::s_program_uniform_matrix_functions<float>;
    template<> const Program::GLProgramUniformMatrixFunctions<double>   Program::s_program_uniform_matrix_functions<double>;

    template<auto N, class T, auto Q>
    constexpr auto Program::s_glProgramUniform<glm::vec<N, T, Q>> =
            [] (GLuint program, GLint location, glm::vec<N, T, Q> value)
            {
                static_assert(N > 1 && N < 5, "N may only be 2, 3 or 4");

                if constexpr (N == 2)
                    s_glCall(s_program_uniform_functions<T>._2)(program, location, value.x, value.y);
                else if constexpr (N == 3)
                    s_glCall(s_program_uniform_functions<T>._3)(program, location, value.x, value.y, value.z);
                else if constexpr (N == 4)
                    s_glCall(s_program_uniform_functions<T>._4)(program, location, value.x, value.y, value.z. value.w);
            };

    template<auto N, class T, auto Q>
    constexpr auto Program::s_glProgramUniformv<glm::vec<N, T, Q>> =
            [](GLuint program, GLint location, GLsizei count, const glm::vec<N, T, Q>* values)
            {
                static_assert(N > 1 && N < 5, "N may only be 2, 3 or 4");

                s_glCall(s_program_uniform_v_functions<T>[N - 1])(program, location, count, glm::value_ptr(values));
            };

} // glutils


#endif //SIMPLERENDERER_PROGRAM_HPP
