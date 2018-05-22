project(glitter-benchmarks
    VERSION 0.0
    LANGUAGES CXX
)

add_executable(glitter-benchmarks
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(glitt::glitter-benchmarks
    ALIAS
        glitter-benchmarks
)

target_link_libraries(glitter-benchmarks
    INTERFACE
        glitt::compile-options-private
)

if (MSVC)
    target_link_libraries(glitter-benchmarks
        PRIVATE
            glitt::ext_google_benchmark $<$<CONFIG:Release>:-LTCG>
    )
else()
    target_link_libraries(glitter-benchmarks
        PRIVATE
            glitt::ext_google_benchmark
    )
endif()
