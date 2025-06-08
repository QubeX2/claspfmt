cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_COMPILER "/usr/bin/clang++")
project (claspfmt
  VERSION 0.1.0
  DESCRIPTION "Classic Asp Formatter"
  LANGUAGES CXX
)
add_executable(claspfmt 
  src/main.cpp
  src/tokenizer.cpp
  src/ast.cpp
  src/mikandr.cpp
)
