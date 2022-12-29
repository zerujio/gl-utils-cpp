#include "glutils/gl.hpp"

namespace GL {

    thread_local GladGLContext gl;

    int loadGLContext(GLADloadfunc load_func) {
        return gladLoadGLContext(&gl, load_func);
    }

} // GL
