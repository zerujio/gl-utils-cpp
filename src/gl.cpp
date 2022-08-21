#include "glutils/gl.h"

namespace glutils {

    thread_local GladGLContext gl;

    int loadGLContext(GLADloadfunc load_func) {
        return gladLoadGLContext(&gl, load_func);
    }

} // glutils
