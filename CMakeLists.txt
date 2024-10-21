cmake_minimum_required(VERSION 3.27)

include(cmake/modules.cmake)
include(GitVersion)

project(conftools
    VERSION ${GIT_VERSION_ABBREV}
    DESCRIPTION "Common utilities and conversions for C++ programs"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

include(ProjectTesting)
include(packages.cmake)

add_library(conftools)
add_library(${PROJECT_NAME}::conftools ALIAS conftools)
target_sources(conftools PUBLIC FILE_SET HEADERS BASE_DIRS include)
target_link_libraries(conftools
    PUBLIC
        ext::ext
        fmt::fmt
        netcore::netcore
        timber::timber
        yaml-cpp::yaml-cpp
)

if(PROJECT_TESTING)
    add_executable(conftools.test)
    target_link_libraries(conftools.test
        PRIVATE
            conftools
            GTest::gtest_main
    )
    add_test(
        NAME "Unit Tests"
        COMMAND conftools.test
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )
endif()

add_subdirectory(include)
add_subdirectory(src)

include(Sanitizers)
enable_asan()

include(EasyInstall)
easy_install(
    TARGETS conftools
    DEPENDENCIES
        ext
        fmt
        netcore
        timber
        yaml-cpp
)

if(PROJECT_IS_TOP_LEVEL)
    add_custom_target(docker
        docker build --progress=plain .
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        USES_TERMINAL
    )
endif()

