#ifndef SIMPLERENDERER_PROGRAM_HPP
#define SIMPLERENDERER_PROGRAM_HPP

#include "handle.hpp"
#include "shader.hpp"

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

        std::string getInfoLog() const;

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
    };

} // glutils


#endif //SIMPLERENDERER_PROGRAM_HPP
