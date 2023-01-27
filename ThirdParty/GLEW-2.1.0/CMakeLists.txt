cmake_minimum_required (VERSION 3.8.2)

add_library (GLEW STATIC "Source/glew.c")
target_compile_definitions (GLEW PUBLIC GLEW_STATIC)
target_include_directories (GLEW PUBLIC "Include")
