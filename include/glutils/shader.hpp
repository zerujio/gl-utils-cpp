#ifndef SIMPLERENDERER_SHADER_HPP
#define SIMPLERENDERER_SHADER_HPP

#include "handle.hpp"

namespace glutils {

    class Shader : public BaseHandle<&GladGLContext::IsShader>
    {
    public:
        Shader() = default;

        enum class Type {
            compute         = GL_COMPUTE_SHADER,
            vertex          = GL_VERTEX_SHADER,
            tess_control    = GL_TESS_CONTROL_SHADER,
            tess_evaluation = GL_TESS_EVALUATION_SHADER,
            geometry        = GL_GEOMETRY_SHADER,
            fragment        = GL_FRAGMENT_SHADER
        };

        static auto create(Type type) -> Shader;

        static void destroy(Shader shader);

        /// Replaces the source code in the shader object
        /**
         * glShaderSource sets the source code in shader to the source code in the array of strings specified by
         * @p string. Any source code previously stored in the shader object is completely replaced. The number of
         * strings in the array is specified by @p count. If @p length is NULL, each string is assumed to be null
         * terminated. If @p length is a value other than NULL, it points to an array containing a string length
         * for each of the corresponding elements of @p string. Each element in the @p length array may contain the
         * length of the corresponding string (the null character is not counted as part of the string length) or a
         * value less than 0 to indicate that the string is null terminated. The source code strings are not scanned
         * or parsed at this time; they are simply copied into the specified shader object.
         *
         * Notes:
         * OpenGL copies the shader source code strings when glShaderSource is called, so an application may free its
         * copy of the source code strings immediately after the function returns.
         *
         * @param count     Specifies the number of elements in the string and length arrays.
         * @param string    Specifies an array of pointers to strings containing the source code to be loaded into
         *                  the shader.
         * @param length    Specifies an array of string lengths.
         */
        void setSource(GLsizei count, const GLchar **string, const GLint *length = nullptr) const;

        /// Compiles the shader object.
        void compile() const;

        enum class Parameter
        {
            type            = GL_SHADER_TYPE,
            delete_status   = GL_DELETE_STATUS,
            compile_status  = GL_COMPILE_STATUS,
            info_log_length = GL_INFO_LOG_LENGTH,
            source_length   = GL_SHADER_SOURCE_LENGTH
        };

        [[nodiscard]]
        auto getParameter(Parameter parameter) const -> GLint;

        /// glGetShaderInfoLog - Returns the information log for a shader object.
        void getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const;

    private:
        using BaseHandle::BaseHandle;
    };

} // glutils

#endif //SIMPLERENDERER_SHADER_HPP
