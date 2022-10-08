#ifndef PROCEDURALPLACEMENTLIB_INTERFACE_BLOCK_HPP
#define PROCEDURALPLACEMENTLIB_INTERFACE_BLOCK_HPP

#include "gl_types.hpp"
#include "program.hpp"
#include "error.hpp"

namespace glutils {

    enum class InterfaceBlockType
    {
        uniform = 0x92E2,
        shader_storage = 0x92E6
    };

    class BaseInterfaceBlockInfo
    {
        friend class BaseInterfaceBlockProxy;
    public:
        [[nodiscard]] GLuint getBinding() const {return m_binding_index;}

    protected:
        /**
         * @brief Query the @p Type interface block named @p name in @p program
         * @param program The program containing the interface block.
         * @param name The name of the interface block.
         */
        BaseInterfaceBlockInfo(Program program, const std::string& name, InterfaceBlockType type);

    private:
        GLuint m_resource_index;
        GLuint m_binding_index;
    };

    template <InterfaceBlockType Type>
    class InterfaceBlockInfo final : public BaseInterfaceBlockInfo
    {
    public:
        InterfaceBlockInfo(Program program, const char* name) : BaseInterfaceBlockInfo(program, name, Type) {}
    };
    using UniformBlockInfo = InterfaceBlockInfo<InterfaceBlockType::uniform>;
    using ShaderStorageBlockInfo = InterfaceBlockInfo<InterfaceBlockType::shader_storage>;

    class BaseInterfaceBlockProxy
    {
    public:
        [[nodiscard]] GLuint getBinding() const { return m_info.m_binding_index; }

    protected:
        BaseInterfaceBlockProxy(Program program, BaseInterfaceBlockInfo& info) : m_program(program), m_info(info) {}

        [[nodiscard]] GLuint m_getResourceIndex() const {return m_info.m_resource_index;}
        void m_setBinding(GLuint index) {m_info.m_resource_index = index;}
        [[nodiscard]] Program m_getProgram() const {return m_program;}
    private:
        Program m_program;
        BaseInterfaceBlockInfo& m_info;
    };

    /// Allows the modification of shader storage block binding point.
    class ShaderStorageBlockProxy final : public BaseInterfaceBlockProxy
    {
    public:
        ShaderStorageBlockProxy(Program program, ShaderStorageBlockInfo &info) : BaseInterfaceBlockProxy(program, info) {}

        void setBinding(GLuint index);
    };

    /// Allows the modification of uniform block binding point.
    class UniformBlockProxy final : public BaseInterfaceBlockProxy
    {
    public:
        UniformBlockProxy(Program program, UniformBlockInfo& info) : BaseInterfaceBlockProxy(program, info) {}

        void setBinding(GLuint index);
    };

} // glutils

#endif //PROCEDURALPLACEMENTLIB_INTERFACE_BLOCK_HPP
