# CMake settings
# --------------

cmake_minimum_required (VERSION 3.0)
find_package(PkgConfig REQUIRED)


# Global variables
# ----------------
set (NAME "Template")
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")
set (INCLUDE_DIRS "src/" "dependencies/include")


# Project
# -------
project (${NAME})
include_directories(${INCLUDE_DIRS})
add_executable (${NAME} ${SOURCES})


# Libraries
# ---------

# AndTweakBar
target_link_libraries (${NAME} ${CMAKE_SOURCE_DIR}/dependencies/lib/libAntTweakBar.a)

# Assimp
pkg_search_module (ASSIMP REQUIRED assimp)
include_directories (${ASSIMP_INCLUDE_DIRS})
target_link_libraries (${NAME} ${ASSIMP_STATIC_LIBRARIES})

# GLEW
find_package(GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})
target_link_libraries (${NAME} ${GLEW_LIBRARIES})

# GLFW
pkg_search_module (GLFW REQUIRED glfw3)
include_directories (${GLFW_INCLUDE_DIRS})
target_link_libraries (${NAME} ${GLFW_STATIC_LIBRARIES})  # or GLFW_LIBRARIES


# Enable C++ features
# -------------------
target_compile_features (${NAME} PRIVATE cxx_nullptr)
