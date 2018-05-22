project(tests
    VERSION 0.0
    LANGUAGES CXX
)

add_executable(tests
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(glitt::tests
    ALIAS
        tests
)

target_link_libraries(tests
    INTERFACE
        glitt::compile-options-private
    PRIVATE
        glitt::ext_google_test
)
