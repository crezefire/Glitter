project(glitter
    VERSION 0.0
    LANGUAGES CXX
)

add_library(glitter
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vulkan/vulkan-helpers.cpp
)

source_group(src
    REGULAR_EXPRESSION
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)

source_group(src\\vulkan
    REGULAR_EXPRESSION
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vulkan/*
)

add_library(glitt::glitter
    ALIAS
        glitter
)

target_include_directories(glitter
    PUBLIC
        $<BUILD_INTERFACE:${glitter_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${glitter_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

find_package(Vulkan REQUIRED)

target_link_libraries(glitter
    PRIVATE
        glitt::compile-options-private
    PUBLIC
        glitt::compile-options-public
        Vulkan::Vulkan
		gget::gadget
)

target_compile_definitions(glitter
	PRIVATE
		VK_PROTOTYPES=1
)

if (MSVC)
    target_compile_definitions(glitter
        PRIVATE
			VK_USE_PLATFORM_WIN32_KHR=1
    )
endif()

install(
    TARGETS
        glitter
    EXPORT
        glitterTargets
    LIBRARY DESTINATION
        lib
    ARCHIVE DESTINATION
        lib
    RUNTIME DESTINATION
        bin
    INCLUDES DESTINATION
        include
    PUBLIC_HEADER DESTINATION
        include
)

install(
    DIRECTORY
        include/
    DESTINATION
        include
)

install(
    EXPORT
        glitterTargets
    FILE
        glitterTargets.cmake
    NAMESPACE
        glitt::
    DESTINATION
        lib/cmake/glitter
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "glitterConfigVersion.cmake"
    VERSION
        ${glitter_VERSION}
    COMPATIBILITY
        SameMajorVersion
)

install(
    FILES
        "glitterConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/glitterConfigVersion.cmake"
    DESTINATION
        lib/cmake/glitter
)

export(
    PACKAGE
        glitter
)
