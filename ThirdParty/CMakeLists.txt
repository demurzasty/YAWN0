cmake_minimum_required (VERSION 3.8.2)

add_subdirectory ("CGLTF-1.13")

add_subdirectory ("GLEW-2.1.0")

set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory ("googletest-1.13.0")

add_subdirectory ("imgui-docking-1.89.2")

add_subdirectory ("LUA-5.4.4")

add_subdirectory ("STB")
