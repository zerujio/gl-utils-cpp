add_library(glad STATIC $<IF:$<CONFIG:Debug>, src/gl-debug.c, src/gl.c>)
target_include_directories(glad PUBLIC glad/include-khr $<IF:$<CONFIG:Debug>, include-debug, include-release>)