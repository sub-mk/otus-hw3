cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION 1)
endif()

project(allocator VERSION 0.0.${VERSION})

add_executable(allocator allocator.cpp)
add_library(lib lib.cpp)
target_link_libraries(allocator lib)
target_include_directories(lib
        PRIVATE "${CMAKE_BINARY_PATH}")

install(TARGETS allocator RUNTIME DESTINATION bin)

# Debian package
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mklib@yandex.ru)

include(CPack)
### ###

### gtest ###
find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(test_allocator test_allocator.cpp)
target_link_libraries(test_allocator
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        lib)

target_include_directories(test_allocator PRIVATE
        ${GTEST_INCLUDE_DIRS}
        )

enable_testing()
add_test(test_allocator test_allocator)
### ###

# Set strict compiler flags
if (MSVC)
    target_compile_options(allocator PRIVATE
            /W4
            )
    target_compile_options(test_allocator PRIVATE
            /W4
            )
else ()
    target_compile_options(allocator PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(test_allocator PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()
### ###
