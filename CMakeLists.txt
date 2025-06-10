cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project (claspfmt
  VERSION 0.1.0
  DESCRIPTION "Classic Asp Formatter"
  LANGUAGES CXX
)

set(EXECUTABLE_OUTPUT_PATH "bin")
add_executable(claspfmt)
add_subdirectory(libs/mikandr)
add_subdirectory(src)
target_include_directories(claspfmt PUBLIC libs/mikandr)
target_link_libraries(claspfmt PUBLIC mikandr)
