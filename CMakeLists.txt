cmake_minimum_required (VERSION 3.8.2)

project (YAWN)

add_subdirectory ("ThirdParty")

add_executable (BinaryToHeader "Source/Tools/BinaryToHeader.cpp")

file (GLOB_RECURSE GLSL_SOURCE_FILES "Source/*.vert" "Source/*.frag" "Source/*.comp" "Source/*.spv")
foreach (GLSL_SRC ${GLSL_SOURCE_FILES})
	get_filename_component (FILE_DIRECTORY ${GLSL_SRC} DIRECTORY)
	get_filename_component (FILE_NAME ${GLSL_SRC} NAME)
	get_filename_component (FILE_EXT ${GLSL_SRC} EXT)

	set (GLSL_H "${FILE_DIRECTORY}/Generated/${FILE_NAME}.h")

	string (REPLACE "." "_" VARIABLE_NAME ${FILE_NAME})

	add_custom_command (
		OUTPUT ${GLSL_H}
		COMMAND BinaryToHeader ${GLSL_SRC} ${GLSL_H} "${VARIABLE_NAME}" # GLSL -> C Header
		DEPENDS ${GLSL_SRC}
	)
	list (APPEND GLSL_BINARY_FILES ${GLSL_H})
endforeach (GLSL_SRC)
add_custom_target (Shaders DEPENDS ${GLSL_BINARY_FILES})

set (SRC 
	"Source/Application.cpp"
	"Source/Component.cpp"
	"Source/GraphicsDevice.cpp"
	"Source/GraphicsResource.cpp"
	"Source/Main.cpp"
	"Source/Math.cpp"
	"Source/Mesh.cpp"
	"Source/Actor.cpp"
	"Source/Platform.cpp"
	"Source/Reference.cpp"
	"Source/Scene.cpp"
	"Source/Settings.cpp"
	"Source/String.cpp"
	"Source/Texture.cpp"
	"Source/TypeReflect.cpp"
	"Source/UI.cpp"
	"Source/Variant.cpp"
)

if (WIN32)
	set (SRC ${SRC}
		"Source/Win32/MainWin32.cpp"
		"Source/Win32/PlatformWin32.cpp"
	)
endif ()

set (SRC ${SRC}
	"Source/OpenGL/GraphicsDeviceOpenGL.cpp"
	"Source/OpenGL/ShadersOpenGL.cpp"
	"Source/OpenGL/UtilsOpenGL.cpp"
)

if (WIN32)
	set (SRC ${SRC}
		"Source/OpenGL/Win32/GraphicsContextOpenGLWin32.cpp"
	)
endif ()

add_library (YAWN STATIC ${SRC})
target_compile_features (YAWN PUBLIC cxx_std_17)
target_include_directories (YAWN PUBLIC "Include")
target_compile_definitions (YAWN PRIVATE _CRT_SECURE_NO_WARNINGS)
target_link_libraries (YAWN PRIVATE ImGUI STB CGLTF LUALIB GLEW OpenGL32)
add_dependencies (YAWN Shaders)

add_executable (YAWN_Tests "Source/Tests/Managed.cpp")
target_link_libraries (YAWN_Tests PUBLIC YAWN gtest)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	add_subdirectory ("Example")
endif ()
