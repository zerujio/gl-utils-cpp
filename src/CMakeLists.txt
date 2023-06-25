add_library(glutils STATIC
        gl.cpp
        program.cpp
        shader.cpp
        buffer.cpp
        vertex_array.cpp
        glsl_syntax.cpp
        sync.cpp
        texture.cpp)
target_include_directories(glutils PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(glutils PUBLIC glad glm)
target_compile_definitions(glutils PUBLIC GLUTILS_DEBUG=$<CONFIG:Debug>)