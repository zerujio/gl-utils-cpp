#include "glutils/glsl_syntax.hpp"

#include <array>

namespace GL {

    struct StringJoiner
    {
        std::ostream &out;
        const char * separator = " ";
        unsigned int items = 0;

        template<class T>
        auto add(const T &value) -> StringJoiner &
        {
            if (items++)
                out << separator;
            out << value;
            return *this;
        }

        template<class T>
        auto addIf(const T &value, const T &null_value) -> StringJoiner &
        {
            if (value != null_value)
                add(value);
            return *this;
        }

        template<class T>
        auto addIf(const T &value) -> StringJoiner &
        {
            if (bool(value))
                add(value);
            return *this;
        }

        template<class T>
        auto addStringIf(const char* c_str, const T& value, const T& null_value) -> StringJoiner &
        {
            if (value != null_value)
                add(c_str);
            return *this;
        }

        template<class T>
        auto addStringIf(const char* c_str, const T& value) -> StringJoiner &
        {
            if (bool(value))
                add(c_str);
            return *this;
        }
    };


    auto operator<<(std::ostream &out, Type type) -> std::ostream &
    {
        const std::array type_strings
                {
                        "float", "vec2", "vec3", "vec4",
                        "int", "ivec2", "ivec3", "ivec4",
                        "uint", "uvec2", "uvec3", "uvec4",
                        "mat2", "mat3", "mat4",
                        "sampler2D"
                };
        return out << type_strings[static_cast<unsigned int>(type)];
    }

    auto operator<<(std::ostream &out, LayoutQualifiers::Memory memory) -> std::ostream &
    {
        const std::array strings {"", "packed", "shared", "std140", "std430"};
        return out << strings[static_cast<unsigned int>(memory)];
    }

    auto operator<<(std::ostream &out, StorageQualifier qualifier) -> std::ostream &
    {
        const std::array qualifier_strings {"", "const", "in", "out", "uniform", "buffer"};
        return out << qualifier_strings[static_cast<unsigned int>(qualifier)];
    }

    struct LayoutQualifier
    {
        const char *name;
        int value;

        operator bool () const {return value > -1;}
    };

    auto operator<<(std::ostream &out, const LayoutQualifier &qualifier) -> std::ostream  &
    {
        if (qualifier.name)
            out << qualifier.name << " = " << qualifier.value;
        return out;
    }

    auto operator<<(std::ostream &out, const LayoutQualifiers &layout) -> std::ostream &
    {
        using Memory = LayoutQualifiers::Memory;

        out << "layout(";

        StringJoiner joiner {out, ", "};
        joiner.addIf(layout.memory, Memory::none)
            .addIf(LayoutQualifier{"location", layout.location})
            .addIf(LayoutQualifier{"component", layout.component})
            .addIf(LayoutQualifier{"binding", layout.binding});

        return out << ')';
    }

    auto operator<<(std::ostream &out, Initializer init) -> std::ostream &
    {
        return out << "= " << init.ctor_string;
    }

    struct ArraySize
    {
        int size;
        operator bool() const {return size;}
    };

    auto operator<<(std::ostream& out, ArraySize size) -> std::ostream &
    {
        if (size.size < 0)
            return out << "[]";
        else
            return out << '[' << size.size << ']';
    }

    auto operator<<(std::ostream &out, const Definition &decl) -> std::ostream &
    {
        StringJoiner join {out, " "};
        join.addIf(decl.layout)
            .addIf(decl.storage, StorageQualifier::none)
            .add(decl.type)
            .add(decl.name)
            .addIf(ArraySize{decl.array_size})
            .addIf(decl.init);
        return out << ';';
    }

    LayoutQualifiers::operator bool() const
    {
        return memory != Memory::none || location != -1 || binding != -1;
    }

    auto operator|(MemoryQualifier l, MemoryQualifier r) -> MemoryQualifier
    {
        using underlying_type = std::underlying_type_t<MemoryQualifier>;
        return static_cast<MemoryQualifier>(static_cast<underlying_type>(l) | static_cast<underlying_type>(r));
    }
    auto operator&(MemoryQualifier l, MemoryQualifier r) -> MemoryQualifier
    {
        using underlying_type = std::underlying_type_t<MemoryQualifier>;
        return static_cast<MemoryQualifier>(static_cast<underlying_type>(l) & static_cast<underlying_type>(r));
    }

    auto operator<<(std::ostream& out, MemoryQualifier qualifier) -> std::ostream &
    {
        StringJoiner join {out, " "};
        join.addStringIf("coherent", qualifier & MemoryQualifier::coherent, MemoryQualifier::none);
        join.addStringIf("volatile", qualifier & MemoryQualifier::volatile_, MemoryQualifier::none);
        join.addStringIf("restrict", qualifier & MemoryQualifier::restrict, MemoryQualifier::none);
        join.addStringIf("readonly", qualifier & MemoryQualifier::readonly, MemoryQualifier::none);
        join.addStringIf("writeonly", qualifier & MemoryQualifier::writeonly, MemoryQualifier::none);

        return out;
    }

    auto operator<<(std::ostream &out, const BlockDefinition &block_def) -> std::ostream &
    {
        StringJoiner join {out, " "};
        join.addIf(block_def.layout)
            .addIf(block_def.memory, MemoryQualifier::none)
            .add(block_def.storage)
            .add(block_def.block_name);
        out << "\n{";
        join.separator = "\n  ";
        for (const auto &def : block_def.defs)
            join.add(def);
        out << "\n}";
        join.separator = " ";
        join.addIf(block_def.instance_name);
        return out << ";";
    }
} // simple