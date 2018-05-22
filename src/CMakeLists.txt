if (GLITTER_ENABLE_BENCHMARKING)
    add_subdirectory(benchmarks)
    set_property(TARGET benchmarks PROPERTY FOLDER "src")
endif()

if (GLITTER_ENABLE_TESTING)
    add_subdirectory(tests)
    set_property(TARGET tests PROPERTY FOLDER "src")
endif()
