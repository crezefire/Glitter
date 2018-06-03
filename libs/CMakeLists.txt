# External libraries
if (GLITTER_ENABLE_BENCHMARKING AND NOT TARGET benchmark)
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_EXCEPTIONS OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_LTO ON CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

    if (GLITTER_USE_LIBCXX)
        set(BENCHMARK_USE_LIBCXX ON CACHE BOOL "" FORCE)
    endif()
    
    add_subdirectory(external/google/benchmark/ external/google/benchmark)

    add_library(glitt::ext_google_benchmark
        ALIAS
            benchmark
    )

    set_property(TARGET benchmark PROPERTY FOLDER "external-libs")
endif()

if (GLITTER_ENABLE_TESTING AND NOT TARGET gtest_main)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(BUILD_GTEST ON CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(INSTALL_GMOCK OFF CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(external/google/googletest/ external/google/googletest)

    add_library(glitt::ext_google_test
        ALIAS
            gtest_main
    )

    set_property(TARGET gtest_main PROPERTY FOLDER "external-libs")
    set_property(TARGET gtest PROPERTY FOLDER "external-libs")
endif()

if (GLITTER_ENABLE_BENCHMARKING)
    set(DIMENSION_ENABLE_BENCHMARKING ON CACHE BOOL "" FORCE)
    set(OSS_ENABLE_BENCHMARKING ON CACHE BOOL "" FORCE)
    set(GADGET_ENABLE_BENCHMARKING ON CACHE BOOL "" FORCE)
    set(JARS_ENABLE_BENCHMARKING ON CACHE BOOL "" FORCE)
endif()

if (GLITTER_ENABLE_TESTING)
    set(DIMENSION_ENABLE_TESTING ON CACHE BOOL "" FORCE)
    set(GADGET_ENABLE_TESTING ON CACHE BOOL "" FORCE)
    set(JARS_ENABLE_TESTING ON CACHE BOOL "" FORCE)
    set(OSS_ENABLE_TESTING ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(external/crezefire/dimension/)
add_subdirectory(external/crezefire/gadget/)
add_subdirectory(external/crezefire/jars/)
add_subdirectory(external/crezefire/oss/)

# Internal libraries
add_subdirectory(compile-interfaces/compile-options-private/)
add_subdirectory(compile-interfaces/compile-options-public/)

add_subdirectory(glitter/)
set_property(TARGET glitter PROPERTY FOLDER "libs")
