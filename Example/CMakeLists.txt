cmake_minimum_required (VERSION 3.8.2)

add_executable (Example "Source/Main.cpp")
target_link_libraries (Example PUBLIC YAWN)

add_custom_command(
    TARGET Example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CMAKE_CURRENT_SOURCE_DIR}/Data
            ${CMAKE_CURRENT_BINARY_DIR}/Data
)
