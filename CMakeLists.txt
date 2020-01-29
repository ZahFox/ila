cmake_minimum_required(VERSION 3.12)
# set (CMAKE_CXX_STANDARD 17)

project(ila)

# if ( CMAKE_BUILD_TYPE STREQUAL "" )
# 	set(
# 		CMAKE_BUILD_TYPE
# 			"Debug"
# 		CACHE STRING
# 			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
# 		FORCE
# 	)
# endif ( CMAKE_BUILD_TYPE STREQUAL "" )

# if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
# add_definitions( -O2 )
# endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

file(
	GLOB_RECURSE HDRS 
	${ila_SOURCE_DIR}/src/*.hpp
  ${ila_SOURCE_DIR}/src/*.h
)

file(
  GLOB_RECURSE SRCS
  ${ila_SOURCE_DIR}/src/*.cpp
  ${ila_SOURCE_DIR}/src/*.c
)

include_directories(
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
)
	
	
add_executable(ila ${HDRS} ${SRCS})
	
target_link_libraries(
	ila
	GLEW
	SDL2
	GL
)