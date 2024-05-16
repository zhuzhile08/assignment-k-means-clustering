cmake_minimum_required(VERSION 3.24.0)
project(KMeansClustering VERSION 0.5.0)

set(CMAKE_CXX_STANDARD 23)


# Include sub-projects.
add_subdirectory ("3rdParty")


# project options
option(BUILD_STATIC "Build project statically" ON)
if (BUILD_STATIC)
	option(BUILD_SHARED_LIBS OFF)
else ()
	option(BUILD_SHARED_LIBS ON)
endif()

# MacOS compiler path
if (APPLE)
	set( CMAKE_CXX_COMPILER "/usr/bin/clang++" )
	set( CMAKE_C_COMPILER "/usr/bin/clang" )
endif()

# 3rd party library path
set(LIBRARY_PATH ${CMAKE_SOURCE_DIR}/3rdParty)

# set the local include directory for the engine
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

# copy data files to the build location
add_custom_target(copy_data
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data/
)


# includes and stuff
include_directories(
PUBLIC
	# library local include directory
	${INCLUDE_DIR}

	# graphics and windowing libraries
	${LIBRARY_PATH}/matplotpp/scoure/

	# math and physics libraries
	${LIBRARY_PATH}/glm/

	# utility libraries
	${LIBRARY_PATH}/fmt/include/
)

set (PROJECT_SOURCE_FILES 
	"src/Common/FileSystem.cpp"
	"src/Common/Logger.cpp"


	"src/KMeansClustering.cpp"
	"src/main.cpp"
)

# building the library
if (BUILD_STATIC)
	add_executable(KMeansClustering "${PROJECT_SOURCE_FILES}")
else ()
	add_executable(KMeansClustering "${PROJECT_SOURCE_FILES}")
endif ()

# build error level
if (WIN32) 
	target_compile_options(KMeansClustering PRIVATE /WX)
else () 
	target_compile_options(KMeansClustering PRIVATE -Wall -Wextra -Wpedantic)
endif ()

# add copy dependency
add_dependencies(KMeansClustering copy_data)

# link libraries
target_link_libraries(KMeansClustering
LINK_PUBLIC
	# graphics and windowing libraries
	matplot

	# utility libraries
	fmt::fmt
)
