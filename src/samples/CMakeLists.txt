project(glitter-samples
    VERSION 0.0
    LANGUAGES CXX
)

add_executable(glitter-samples
    ${CMAKE_CURRENT_SOURCE_DIR}/sample0.cpp
)

add_executable(glitt::glitter-samples
    ALIAS
        glitter-samples
)

set_property(TARGET glitter-samples APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

target_link_libraries(glitter-samples
    INTERFACE
        glitt::compile-options-private
    PRIVATE
        glitt::glitter
        oss::oss
)
