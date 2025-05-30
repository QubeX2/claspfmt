cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 11)
project (claspfmt
  VERSION 0.1.0
  DESCRIPTION "Classic Asp Formatter"
  LANGUAGES CXX
)
add_executable(claspfmt src/main.cpp src/prepare.cpp src/format.cpp)
