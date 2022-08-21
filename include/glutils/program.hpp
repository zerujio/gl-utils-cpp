#ifndef SIMPLERENDERER_PROGRAM_HPP
#define SIMPLERENDERER_PROGRAM_HPP

#include "handle.hpp"
#include "shader.hpp"

namespace glutils {

    class Program : public BaseHandle<&GladGLContext::IsProgram>
    {
    public:
        Program() = default;

        static auto create() -> Program;

        static void destroy(Program program);

        /// Installs a program object as part of current rendering state. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
        void use() const;

        /// glLinkProgram - Links a program object. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
        void link() const;

        /// assign a binding point to an active uniform block. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniformBlockBinding.xhtml
        void setBlockBinding(GLuint index, GLuint binding) const;

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
            delete_status                   = GL_DELETE_STATUS,
            link_status                     = GL_LINK_STATUS,
            validate_status                 = GL_VALIDATE_STATUS,
            info_log_length                 = GL_INFO_LOG_LENGTH,
            attached_shaders                = GL_ATTACHED_SHADERS,
            active_atomic_counter_buffers   = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
            active_attributes               = GL_ACTIVE_ATTRIBUTES,
            active_attribute_max_length     = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
            active_uniforms                 = GL_ACTIVE_UNIFORMS,
            active_uniform_blocks           = GL_ACTIVE_UNIFORM_BLOCKS,
            active_uniform_block_max_name_length = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
            active_uniform_max_length       = GL_ACTIVE_UNIFORM_MAX_LENGTH,
            compute_work_group_size         = GL_COMPUTE_WORK_GROUP_SIZE,
            program_binary_length           = GL_PROGRAM_BINARY_LENGTH,
            transform_feedback_buffer_mode  = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
            transform_feedback_varyings     = GL_TRANSFORM_FEEDBACK_VARYINGS,
            transform_feedback_varying_max_length = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
            geometry_vertices_out           = GL_GEOMETRY_VERTICES_OUT,
            geometry_input_type             = GL_GEOMETRY_INPUT_TYPE,
            geometry_output_type            = GL_GEOMETRY_OUTPUT_TYPE
        };

        /// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml
        [[nodiscard]]
        auto getParameter(Parameter parameter) const -> GLint;

        /// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml
        void getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const;

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
        auto getResourceLocation(GLenum interface, const char * name) const -> GLint;

        /// query the index of a named resource within a program. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceIndex.xhtml
        auto getResourceIndex(GLenum interface, const char * name) const -> GLuint;

        /// query the fragment color index of a named variable within a program. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceLocationIndex.xhtml
        auto getResourceLocationIndex(GLenum interface, const char * name) const -> GLint;

        /// query the name of an indexed resource within a program. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResourceName.xhtml
        auto getResourceName(GLenum interface, GLuint index, GLsizei buf_size, GLsizei * length, char * name) const;


    private:
        using BaseHandle::BaseHandle;
    };

} // glutils


#endif //SIMPLERENDERER_PROGRAM_HPP
