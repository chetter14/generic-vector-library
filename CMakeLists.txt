cmake_minimum_required(VERSION 3.28)
project(GenericVector VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message(STATUS "Using MSVC")
	# Has no additional compile options
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message(STATUS "Using clang")
	add_compile_options(-fmodules -fmodules-ts)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	message(STATUS "Using gnu")
	add_compile_options(-fmodules)
endif()

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.17.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
