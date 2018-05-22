cmake_minimum_required(VERSION 3.6)

project(Glitter
    VERSION 0.0
    LANGUAGES CXX
)

# if (NOT EXISTS ${PROJECT_SOURCE_DIR}/libs/external)
#     message(FATAL_ERROR "Please run get_latests_deps.sh before building cmake")
# endif()

option(GLITTER_ENABLE_BENCHMARKING "Build and link google-benchmark lib and executable" OFF)
option(GLITTER_ENABLE_TESTING "Build and link google-test lib and executable" OFF)
option(GLITTER_USE_LIBCXX "Use clangs libcxx. Only works when using clang." OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(libs)
add_subdirectory(src)
