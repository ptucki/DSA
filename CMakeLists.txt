cmake_minimum_required(VERSION 3.28)

project(DSA VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("BUILD TYPE: ${CMAKE_BUILD_TYPE}")

# Add the executable target
add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:/W4 /permissive- /Od /Zi>   # Debug options
    $<$<CONFIG:Release>:/W4 /permissive- /O2 /DNDEBUG> # Release options
  )
endif()
