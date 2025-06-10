project (mikandr
  VERSION 0.1.0
  DESCRIPTION "mikandr shared library"
  LANGUAGES CXX
)

set(LIBRARY_OUTPUT_PATH "lib")
add_library(mikandr SHARED src/mikandr.cpp src/treenode.cpp)

set_target_properties(mikandr 
  PROPERTIES 
  VERSION ${CMAKE_PROJECT_VERSION} 
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

