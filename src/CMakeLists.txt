add_library(glutils STATIC
        gl.cpp
        debug.cpp
        program.cpp
        shader.cpp
        buffer.cpp
        vertex_array.cpp
        glsl_syntax.cpp)
target_include_directories(glutils PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(glutils PUBLIC glad)