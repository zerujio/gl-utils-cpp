#ifndef SIMPLERENDERER_GLSL_SYNTAX_HPP
#define SIMPLERENDERER_GLSL_SYNTAX_HPP

#include <ostream>
#include <vector>

namespace glutils {

    enum class Type
    {
        float_, vec2_, vec3_, vec4_,
        int_ , ivec2_, ivec3_, ivec4_,
        uint_, uvec2_, uvec3_, uvec4_,
        mat2_, mat3_, mat4_,
        sampler2D
    };

    auto operator<<(std::ostream &out, Type type) -> std::ostream &;

    /// layout(...) declaration
    struct LayoutQualifiers final
    {
        enum class Memory
        {
            none,
            packed,
            shared,
            std140,
            std430,
        }
            memory  {Memory::none};
        int location    {-1};
        int component   {-1};
        int binding     {-1};

        operator bool () const;
    };

    auto operator<<(std::ostream &out, LayoutQualifiers::Memory memory) -> std::ostream &;

    auto operator<<(std::ostream &out, const LayoutQualifiers &layout) -> std::ostream &;

    /// GLSL storage qualifier
    enum class StorageQualifier
    {
        none,
        constant,
        in,
        out,
        uniform,
        buffer
    };

    auto operator<<(std::ostream &out, StorageQualifier qualifier) -> std::ostream &;

    struct Initializer
    {
        const char * ctor_string {nullptr};
        operator bool () const {return ctor_string;}
    };

    auto operator<<(std::ostream &out, Initializer init) -> std::ostream &;

    /// A GLSL variable declaration
    struct Definition final
    {
        LayoutQualifiers layout {};
        StorageQualifier storage {StorageQualifier::none};
        Type type {Type::float_};
        const char *name {"unnamed_variable"};
        Initializer init {};
        int array_size {0};
    };

    auto operator<<(std::ostream &out, const Definition &decl) -> std::ostream &;

    enum class MemoryQualifier : unsigned char
    {
        none = 0x0,
        coherent    = 0b1,
        volatile_   = 0b1 << 1,
        restrict    = 0b1 << 2,
        readonly    = 0b1 << 3,
        writeonly   = 0b1 << 4
    };

    auto operator|(MemoryQualifier l, MemoryQualifier r) -> MemoryQualifier;
    auto operator&(MemoryQualifier l, MemoryQualifier r) -> MemoryQualifier;

    auto operator<<(std::ostream& out, MemoryQualifier qualifier) -> std::ostream &;

    struct BlockDefinition
    {
        LayoutQualifiers layout {};
        StorageQualifier storage {StorageQualifier::uniform};
        MemoryQualifier memory {MemoryQualifier::none};
        const char *block_name {"UnnamedBlock"};
        const char *instance_name {nullptr};
        std::vector<Definition> defs;
    };

    auto operator<<(std::ostream &out, const BlockDefinition &block_def) -> std::ostream &;

} // simple

#endif //SIMPLERENDERER_GLSL_SYNTAX_HPP
