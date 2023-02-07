#ifndef SIMPLERENDERER_VERTEX_ARRAY_HPP
#define SIMPLERENDERER_VERTEX_ARRAY_HPP

#include "handle.hpp"
#include "buffer.hpp"
#include "object.hpp"
#include "vertex_attrib_enums.hpp"

namespace GL {

class VertexArrayHandle : public Handle
{
    using Handle::Handle;
public:
    static auto create() -> VertexArrayHandle;

    static void destroy(VertexArrayHandle vertex_array);

    /// glBindVertexArray — bind a vertex array object.
    /**
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
     */
    void bind() const;

    /// glVertexArrayVertexBuffer — bind a buffer to a vertex buffer bind point.
    /**
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexBuffer.xhtml
     * @param binding_index The index of the vertex buffer binding point to which to bind the buffer.
     * @param buffer The name of a buffer to bind to the vertex buffer binding point.
     * @param offset The offset of the first element of the buffer.
     * @param stride The distance between elements within the buffer.
     */
    void bindVertexBuffer(GLuint binding_index, BufferHandle buffer, GLintptr offset, GLsizei stride) const;

    /// glVertexArrayVertexBuffers — attach multiple buffer objects to a vertex array object.
    /**
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexBuffers.xhtml
     * @param first_index Specifies the first vertex buffer binding point to which a buffer object is to be bound.
     * @param count Specifies the number of buffers to bind.
     * @param buffers Specifies the address of an array of names of existing buffer objects.
     * @param offsets Specifies the address of an array of offsets to associate with the binding points.
     * @param strides Specifies the address of an array of strides to associate with the binding points.
     */
    void bindVertexBuffers(GLuint first_index, GLsizei count, const BufferHandle *buffers, const GLintptr *offsets,
                           const GLsizei *strides) const;

    /// glVertexArrayElementBuffer — configures element array buffer binding of a vertex array object.
    /**
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexArrayElementBuffer.xhtml
     * @param buffer Specifies the name of the buffer object to use for the element array buffer binding.
     */
    void bindElementBuffer(BufferHandle buffer) const;

    /// glVertexAttribBinding — associate a vertex attribute and a vertex buffer binding for a vertex array object.
    /**
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribBinding.xhtml
     * @param attribute_index The index of the attribute to associate with a vertex buffer binding.
     * @param binding_index The index of the vertex buffer binding with which to associate the generic vertex attribute.
     */
    void bindAttribute(GLuint attribute_index, GLuint binding_index) const;

    /// glEnableVertexAttribArray — Enable or disable a generic vertex attribute array.
    /**
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
     * @param attribute_index Specifies the index of the generic vertex attribute to be enabled or disabled.
     */
    void enableAttribute(GLuint attribute_index) const;

    void disableAttribute(GLuint attribute_index) const;

    /// glVertexArrayBindingDivisor — modify the rate at which generic vertex attributes advance.
    /**
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexBindingDivisor.xhtml
     * @param index The index of the binding whose divisor to modify.
     * @param divisor The new value for the instance step rate to apply.
     */
    void setBindingDivisor(GLuint binding_index, GLuint divisor) const;

    using AttribSize = VertexAttributeLength;

    using AttribType = VertexAttributeBaseType;

    /// glVertexArrayAttribFormat — specify the organization of vertex arrays.
    /**
     * Use for floating point vertex attributes.
     *
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribFormat.xhtml
     *
     * @param attribute_index The generic vertex attribute array being described.
     * @param size The number of values per vertex that are stored in the array.
     * @param type The type of the data stored in the array.
     * @param normalized Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed. This parameter is ignored if type is GL_FIXED.
     * @param relative_offset The distance between elements within the buffer.
     */
    void setAttribFormat(GLuint attribute_index, AttribSize size, AttribType type, bool normalized,
                         GLuint relative_offset) const;

    /// glVertexArrayAttribFormat — specify the organization of vertex arrays.
    /**
     * Use for integer-valued vertex attributes.
     *
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribFormat.xhtml
     * @param attribute_index The generic vertex attribute array being described.
     * @param size The number of values per vertex that are stored in the array.
     * @param type The type of the data stored in the array.
     * @param relative_offset The distance between elements within the buffer.
     */
    void setAttribIFormat(GLuint attribute_index, AttribSize size, AttribType type,
                          GLuint relative_offset) const;

    /// glVertexArrayAttribFormat — specify the organization of vertex arrays.
    /**
     * Use for 64-bit vertex attributes.
     *
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribFormat.xhtml
     * @param attribute_index The generic vertex attribute array being described.
     * @param size The number of values per vertex that are stored in the array.
     * @param type The type of the data stored in the array.
     * @param relative_offset The distance between elements within the buffer.
     */
    void setAttribLFormat(GLuint attribute_index, AttribSize size, AttribType type,
                          GLuint relative_offset) const;
};

using VertexArray = Object<VertexArrayHandle>;

} // GL

#endif //SIMPLERENDERER_VERTEX_ARRAY_HPP
