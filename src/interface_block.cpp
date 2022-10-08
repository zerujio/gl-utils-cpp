#include "glutils/interface_block.hpp"
#include "glutils/gl.hpp"

namespace glutils {


    BaseInterfaceBlockInfo::BaseInterfaceBlockInfo(Program program, const std::string& name, InterfaceBlockType type)
    {
        m_resource_index = program.getResourceIndex(static_cast<GLenum>(type), name.c_str());
        if (m_resource_index == GL_INVALID_INDEX)
        {
            std::string msg = "No ";
            msg += type == InterfaceBlockType::uniform ? "uniform" : "shader storage";
            msg += " block named ";
            msg += name;
            throw GLError(msg);
        }

        const GLenum prop = GL_BLOCK_INDEX;
        int result = -1;
        program.getResource(static_cast<GLenum>(type), m_resource_index, 1, &prop, 1, nullptr, &result);

        if (result < 0)
            throw GLError("Couldn't get interface block binding index");

        m_binding_index = result;
    }

    void ShaderStorageBlockProxy::setBinding(GLuint index)
    {
        gl.ShaderStorageBlockBinding(m_getProgram().getName(), m_getResourceIndex(), index);
        m_setBinding(index);
    }

    void UniformBlockProxy::setBinding(GLuint index)
    {
        gl.UniformBlockBinding(m_getProgram().getName(), m_getResourceIndex(), index);
        m_setBinding(index);
    }
} // glutils