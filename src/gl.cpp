#include "glutils/gl.h"

void glutils::loadGLContext(GLADloadfunc load_func) {
    gladLoadGLContext(&gl, load_func);
}