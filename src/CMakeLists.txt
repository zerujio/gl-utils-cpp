add_library(glutils STATIC)
target_sources(glutils PRIVATE
        gl.cpp
        buffer.cpp)
target_link_libraries(glutils PUBLIC glad)