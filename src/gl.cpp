#include "glutils/gl.hpp"
#include "glutils/error.hpp"

#if GLUTILS_DEBUG

#include <exception>

#endif

namespace GL {

#if GLUTILS_DEBUG
namespace {

std::exception_ptr g_debug_exception;
std::ostream *g_debug_out{nullptr};
std::ostream *g_debug_err{nullptr};

const char *getDebugMessageSourceString(unsigned int source_enum)
{
    switch (source_enum)
    {
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

const char *getDebugMessageTypeString(unsigned int type_enum)
{
    switch (type_enum)
    {
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

const char *getDebugMessageSeverityString(unsigned int severity_enum)
{
    switch (severity_enum)
    {
#define SEVERITY_CASE(CASE) case GL_DEBUG_SEVERITY_##CASE: return #CASE;
        SEVERITY_CASE(HIGH)
        SEVERITY_CASE(MEDIUM)
        SEVERITY_CASE(LOW)
        SEVERITY_CASE(NOTIFICATION)
        default:
            return "??";
    }
}

void
debugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei, const char *message, const void *)
{
    const bool is_error = type == GL_DEBUG_TYPE_ERROR;

    if (is_error)
        g_debug_exception = std::make_exception_ptr(Error(message));

    if (!g_debug_out)
        return;

    std::ostream &out = (g_debug_err && is_error) ? *g_debug_err : *g_debug_out;

    out << "[OpenGL Debug Message] (" << id << ")"
        << "\nSource:   " << getDebugMessageSourceString(source)
        << "\nType:     " << getDebugMessageTypeString(type)
        << "\nSeverity: " << getDebugMessageSeverityString(severity)
        << "\nMessage:  " << message
        << "\n";
}

void postCall(void *, const char *, GLADapiproc, int, ...)
{
    if (g_debug_exception)
    {
        std::exception_ptr ptr;
        g_debug_exception.swap(ptr);
        std::rethrow_exception(ptr);
    }
}

}
#endif // GLUTILS_DEBUG

int loadContext(GLADloadfunc loader)
{
    const int version = gladLoadGL(loader);

    if (version == 0)
        throw Error("failed to load functions for OpenGL context");

#if GLUTILS_DEBUG
    {
        GLint flags = 0;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

        if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT))
            throw Error("glutils was built in debug mode but current OpenGL context is not a debug context");
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);
    gladSetGLPostCallback(postCall);
#endif // GLUTILS_DEBUG

    return version;
}

#if GLUTILS_DEBUG

void enableDebugMessages(std::ostream *out, std::ostream *err)
{
    g_debug_out = out;
    g_debug_err = err;
}

#endif // GLUTILS_DEBUG

} // GL
