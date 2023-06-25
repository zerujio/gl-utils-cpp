#ifndef GLUTILS_GL_H
#define GLUTILS_GL_H

#include "glad/gl.h"

#ifndef GLUTILS_DEBUG
#define GLUTILS_DEBUG 0
#endif // GLUTILS_DEBUG

#if GLUTILS_DEBUG

#include <iostream>

#endif // GLUTILS_DEBUG

namespace GL {

/// Initializes glutils for the context that's current on the calling thread. Returns the version number of the context.
int loadContext(GLADloadfunc loader);

#if GLUTILS_DEBUG

/**
 * @brief Configure an output stream to write debug messages to.
 * @param out The main output stream. If null, debug messages will stop being printed.
 * @param err The error output stream. If null, error messages will be printed to out, along all other messages.
 */
void enableDebugMessages(std::ostream *out = &std::cout, std::ostream *err = &std::cerr);

#endif // GLUTILS_DEBUG

} // GL

#endif //GLUTILS_GL_H
