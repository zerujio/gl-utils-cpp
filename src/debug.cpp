#include <glutils/debug.hpp>
#include <glutils/gl.hpp>

#include <iostream>

namespace GL {

    auto getDebugMessageSourceString(unsigned int source_enum) -> const char*
    {
        switch (source_enum) {
#define SOURCE_CASE(CASE) case GL_DEBUG_SOURCE_##CASE: return #CASE;;
            SOURCE_CASE(API)
            SOURCE_CASE(WINDOW_SYSTEM)
            SOURCE_CASE(SHADER_COMPILER)
            SOURCE_CASE(THIRD_PARTY)
            SOURCE_CASE(APPLICATION)
            SOURCE_CASE(OTHER)
            default:
                return "??";
        }
    }

    auto getDebugMessageTypeString(unsigned int type_enum) -> const char*
    {
        switch (type_enum) {
#define TYPE_CASE(CASE) case GL_DEBUG_TYPE_##CASE: return #CASE;
            TYPE_CASE(ERROR)
            TYPE_CASE(DEPRECATED_BEHAVIOR)
            TYPE_CASE(UNDEFINED_BEHAVIOR)
            TYPE_CASE(PORTABILITY)
            TYPE_CASE(PERFORMANCE)
            TYPE_CASE(MARKER)
            TYPE_CASE(PUSH_GROUP)
            TYPE_CASE(POP_GROUP)
            TYPE_CASE(OTHER)
            default:
                return "??";
        }
    }

    auto getDebugMessageSeverityString(unsigned int severity_enum) -> const char*
    {
        switch (severity_enum) {
#define SEVERITY_CASE(CASE) case GL_DEBUG_SEVERITY_##CASE: return #CASE;
            SEVERITY_CASE(HIGH)
            SEVERITY_CASE(MEDIUM)
            SEVERITY_CASE(LOW)
            SEVERITY_CASE(NOTIFICATION)
            default:
                return "??";
        }
    }

    void debugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
                       const char *message, const void *user_ptr)
    {
        auto & out = severity == GL_DEBUG_SEVERITY_HIGH ? std::cerr : std::cout;

        out << "[OpenGL Debug Message] (" << id << ")"
            << "\nSource:   " << getDebugMessageSourceString(source)
            << "\nType:     " << getDebugMessageTypeString(type)
            << "\nSeverity: " << getDebugMessageSeverityString(severity)
            << "\nMessage:  " << message
            << "\n";
    }

    void enableDebugCallback() {
        gl.DebugMessageCallback(debugCallback, nullptr);
    }

} // GL