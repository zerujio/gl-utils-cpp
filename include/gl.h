#ifndef GLUTILS_GL_H
#define GLUTILS_GL_H

#include <glad/gl.h>

namespace glutils {

    /// Holds OpenGL functions.
    thread_local GladGLContext gl;

    /// Loads functions from the current OpenGL context.
    void loadGLContext(GLADloadfunc load_func);

} // glutils

#endif //GLUTILS_GL_H
