add_library(glutils STATIC)
target_sources(glutils PRIVATE
        gl.cpp
        buffer.cpp)
target_include_directories(glutils PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(glutils PUBLIC glad)