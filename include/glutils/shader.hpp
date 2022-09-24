#ifndef SIMPLERENDERER_SHADER_HPP
#define SIMPLERENDERER_SHADER_HPP

#include "handle.hpp"

namespace glutils {

    class Shader final : public Handle
    {
        using Handle::Handle;
    public:
        enum class Type {
            compute         = 0x91B9,
            vertex          = 0x8B31,
            tess_control    = 0x8E88,
            tess_evaluation = 0x8E87,
            geometry        = 0x8DD9,
            fragment        = 0x8B30
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
            type            = 0x8B4F,
            delete_status   = 0x8B80,
            compile_status  = 0x8B81,
            info_log_length = 0x8B84,
            source_length   = 0x8B88
        };

        [[nodiscard]]
        auto getParameter(Parameter parameter) const -> GLint;

        /// glGetShaderInfoLog - Returns the information log for a shader object.
        void getInfoLog(GLsizei max_length, GLsizei *length, GLchar *info_log) const;
    };

} // glutils

#endif //SIMPLERENDERER_SHADER_HPP
