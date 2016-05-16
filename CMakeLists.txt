# CMake stuff
# --------------

cmake_minimum_required (VERSION 3.0)
find_package (PkgConfig REQUIRED)
set (MAKE_EXPORT_COMPILE_COMMANDS 1)


# Compiler settings
# -----------------
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "                               \
    ${CMAKE_CXX_FLAGS}                                \
    -O0                                               \
    -ggdb                                             \
    -pedantic                                         \
    -Wabi                                             \
    -Wabi-tag                                         \
    -Waggregate-return                                \
    -Wall                                             \
    -Wcast-align                                      \
    -Wcast-qual                                       \
    -Wconditionally-supported                         \
    -Wconversion                                      \
    -Wctor-dtor-privacy                               \
    -Wdate-time                                       \
    -Wdisabled-optimization                           \
    -Wdouble-promotion                                \
    -Wduplicated-cond                                 \
    -Wextra                                           \
    -Wfloat-conversion                                \
    -Wfloat-equal                                     \
    -Whsa                                             \
    -Winline                                          \
    -Winvalid-pch                                     \
    -Wlogical-op                                      \
    -Wlong-long                                       \
    -Wmissing-declarations                            \
    -Wmissing-field-initializers                      \
    -Wmissing-include-dirs                            \
    -Wmultiple-inheritance                            \
    -Wno-unknown-warning-option                       \
    -Wnoexcept                                        \
    -Wold-style-cast                                  \
    -Wopenmp-simd                                     \
    -Woverloaded-virtual                              \
    -Wpacked                                          \
    -Wpadded                                          \
    -Wpedantic                                        \
    -Wplacement-new=2                                 \
    -Wredundant-decls                                 \
    -Wshadow                                          \
    -Wsign-conversion                                 \
    -Wsign-promo                                      \
    -Wsizeof-pointer-memaccess                        \
    -Wstrict-aliasing=3                               \
    -Wstrict-null-sentinel                            \
    -Wstrict-overflow=5                               \
    -Wsuggest-attribute=const                         \
    -Wsuggest-attribute=noreturn                      \
    -Wsuggest-attribute=pure                          \
    -Wsuggest-final-methods                           \
    -Wsuggest-final-types                             \
    -Wsuggest-override                                \
    -Wswitch-bool                                     \
    -Wswitch-default                                  \
    -Wswitch-enum                                     \
    -Wsync-nand                                       \
    -Wtemplates                                       \
    -Wtrampolines                                     \
    -Wundef                                           \
    -Wuninitialized                                   \
    -Wunsafe-loop-optimizations                       \
    -Wunused-but-set-parameter                        \
    -Wunused-const-variable                           \
    -Wuseless-cast                                    \
    -Wvarargs                                         \
    -Wvariadic-macros                                 \
    -Wvector-operation-performance                    \
    -Wvirtual-inheritance                             \
    -Wzero-as-null-pointer-constant                   \
    ")
endif ()


# Global variables
# ----------------
set (T3D_NAME "Template")
file (GLOB_RECURSE T3D_SOURCES "src/*.c" "src/*.cpp")
include_directories ("src/")
include_directories ("dependencies/include")


# Project
# -------
project (${T3D_NAME})
include_directories (${INCLUDE_DIRS})
add_executable (${T3D_NAME} ${T3D_SOURCES})


# Libraries
# ---------

# AndTweakBar
target_link_libraries (${T3D_NAME} ${CMAKE_SOURCE_DIR}/dependencies/lib/libAntTweakBar.a)

# Assimp
pkg_search_module (ASSIMP REQUIRED assimp)
include_directories (${ASSIMP_INCLUDE_DIRS})
target_link_libraries (${T3D_NAME} ${ASSIMP_STATIC_LIBRARIES})

# GLEW
find_package(GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})
target_link_libraries (${T3D_NAME} ${GLEW_LIBRARIES})

# GLFW
pkg_search_module (GLFW REQUIRED glfw3)
include_directories (${GLFW_INCLUDE_DIRS})
target_link_libraries (${T3D_NAME} ${GLFW_STATIC_LIBRARIES})  # or GLFW_LIBRARIES


# Enable C++ features
# -------------------
target_compile_features (${T3D_NAME} PRIVATE cxx_auto_type)
target_compile_features (${T3D_NAME} PRIVATE cxx_defaulted_functions)
target_compile_features (${T3D_NAME} PRIVATE cxx_lambdas)
target_compile_features (${T3D_NAME} PRIVATE cxx_nullptr)
target_compile_features (${T3D_NAME} PRIVATE cxx_override)
