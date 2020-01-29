cmake_minimum_required (VERSION 3.12)
set (CMAKE_CXX_STANDARD 17)

project (ila)

if(MSVC)
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
	${ila_SOURCE_DIR}/src/*.hpp
  ${ila_SOURCE_DIR}/src/*.h
)

file (
  GLOB_RECURSE SRCS
  ${ila_SOURCE_DIR}/src/*.cpp
  ${ila_SOURCE_DIR}/src/*.c
)

include_directories (
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
)
	
	
add_executable (ila ${HDRS} ${SRCS})
	
target_link_libraries (
	ila
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
)

if(MSVC_IDE)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ila)
endif()