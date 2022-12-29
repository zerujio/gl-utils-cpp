#ifndef GLUTILS_GL_H
#define GLUTILS_GL_H

#include <glad/gl.h>

namespace GL {

    /// Holds OpenGL functions.
    extern thread_local GladGLContext gl;

    /// Loads functions from the current OpenGL context.
    auto loadGLContext(GLADloadfunc load_func) -> int;
} // GL

#endif //GLUTILS_GL_H
