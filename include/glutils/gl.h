#ifndef GLUTILS_GL_H
#define GLUTILS_GL_H

#include <glad/gl.h>

namespace glutils {

    /// Holds OpenGL functions.
    extern thread_local GladGLContext gl;

    /// Loads functions from the current OpenGL context.
    auto loadGLContext(GLADloadfunc load_func) -> int;

} // glutils

#endif //GLUTILS_GL_H
