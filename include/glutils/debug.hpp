#ifndef SIMPLERENDERER_DEBUG_HPP
#define SIMPLERENDERER_DEBUG_HPP

namespace GL {

    /// Calls glDebugMessageCallback and sets up a callback that writes to cout and cerr.
    void enableDebugCallback();

    auto getDebugMessageSourceString(unsigned int source_enum) -> const char*;
    auto getDebugMessageTypeString(unsigned int type_enum) -> const char*;
    auto getDebugMessageSeverityString(unsigned int severity_enum) -> const char*;

} // GL

#endif //SIMPLERENDERER_DEBUG_HPP
