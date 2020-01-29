cmake_minimum_required (VERSION 3.12)
set (CMAKE_CXX_STANDARD 17)


if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	add_definitions(
		-c
		-W4
	)
else()
	add_definitions(
		-c
		-Wall
	)
endif()

project (ila)

if ( CMAKE_BUILD_TYPE STREQUAL "" )
	set (
		CMAKE_BUILD_TYPE
			"Debug"
		CACHE STRING
			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
		FORCE
	)
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
	add_definitions (-O2)
endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )


find_package (OpenGL REQUIRED)

set (ila_CMAKE_DIR "${ila_SOURCE_DIR}/cmake")
include (${ila_CMAKE_DIR}/FindGLEW.cmake)
include (${ila_CMAKE_DIR}/FindSDL2.cmake)

file (
	GLOB_RECURSE HDRS 
	${ila_SOURCE_DIR}/src/*.h
)

file (
	GLOB_RECURSE SRCS
	${ila_SOURCE_DIR}/src/*.cpp
)
	
add_executable (ila ${HDRS} ${SRCS})

target_include_directories (
	ila PRIVATE
	${ila_SOURCE_DIR}/src
	${ila_SOURCE_DIR}/src/Core
	${ila_SOURCE_DIR}/src/Platform
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
)
	
	
	
target_link_libraries (
	ila
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
)

if(MSVC_IDE)
	file (
		GLOB_RECURSE CORE_HDRS 
		${ila_SOURCE_DIR}/src/Core/*.h
	)

	file (
		GLOB_RECURSE CORE_SRCS
		${ila_SOURCE_DIR}/src/Core/*.cpp
	)

	source_group("Source Files\\Core" FILES ${CORE_HDRS} ${CORE_SRCS})

	file (
		GLOB_RECURSE PLATFORM_HDRS 
		${ila_SOURCE_DIR}/src/Platform/*.h
	)

	file (
		GLOB_RECURSE PLATFORM_SRCS
		${ila_SOURCE_DIR}/src/Platform/*.cpp
	)

	source_group("Source Files\\Platform" FILES ${PLATFORM_HDRS} ${PLATFORM_SRCS})

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ila)
endif()