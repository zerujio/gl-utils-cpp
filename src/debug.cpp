#include <glutils/debug.hpp>
#include <glutils/gl.h>

#include <iostream>

namespace glutils {

    void debugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *user_ptr)
    {
        const char* src_str;
        switch (source) {
#define SOURCE_CASE(CASE) case GL_DEBUG_SOURCE_##CASE: src_str = #CASE; break;
            SOURCE_CASE(API)
            SOURCE_CASE(WINDOW_SYSTEM)
            SOURCE_CASE(SHADER_COMPILER)
            SOURCE_CASE(THIRD_PARTY)
            SOURCE_CASE(APPLICATION)
            SOURCE_CASE(OTHER)
            default:
                src_str = "??";
                break;
        }

        const char* type_str;
        switch (type) {
#define TYPE_CASE(CASE) case GL_DEBUG_TYPE_##CASE: type_str = #CASE; break;
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
                type_str = "??";
                break;
        }
        std::cout << std::endl;

        const char* severity_str;
        switch (severity) {
#define SEVERITY_CASE(CASE) case GL_DEBUG_SEVERITY_##CASE: severity_str = #CASE; break;
            SEVERITY_CASE(HIGH)
            SEVERITY_CASE(MEDIUM)
            SEVERITY_CASE(LOW)
            SEVERITY_CASE(NOTIFICATION)
            default:
                severity_str = "??";
                break;
        }

        auto & out = severity == GL_DEBUG_SEVERITY_HIGH ? std::cerr : std::cout;

        out << "\n[OpenGL Debug Message] (" << id << ")"
            << "\nSource:   " << src_str
            << "\nType:     " << type_str
            << "\nSeverity: " << severity_str
            << "\nMessage:  " << message
            << "\n\n";
    }

    void enableDebugCallback() {
        gl.DebugMessageCallback(debugCallback, nullptr);
    }

} // glutils