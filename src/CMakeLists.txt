if (GLITTER_ENABLE_BENCHMARKING)
    add_subdirectory(benchmarks)
    set_property(TARGET glitter-benchmarks PROPERTY FOLDER "benchmarks")
endif()

if (GLITTER_ENABLE_TESTING)
    add_subdirectory(tests)
    set_property(TARGET glitter-tests PROPERTY FOLDER "tests")
endif()

add_subdirectory(samples)
set_property(TARGET glitter-samples PROPERTY FOLDER "samples")
