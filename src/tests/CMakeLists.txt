project(glitter-tests
    VERSION 0.0
    LANGUAGES CXX
)

add_executable(glitter-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(glitt::glitter-tests
    ALIAS
        glitter-tests
)

target_link_libraries(glitter-tests
    INTERFACE
        glitt::compile-options-private
    PRIVATE
        glitt::ext_google_test
)
