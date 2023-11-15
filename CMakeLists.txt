cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    parallel-bfs
    VERSION 0.1.0
    DESCRIPTION "Parallel BFS implementation and benchmarks"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    parallel-bfs_lib OBJECT
    source/lib.cpp
)
target_include_directories(
    parallel-bfs_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

add_library(
    parallel-bfs-test OBJECT
    source/graph.cpp
)

target_include_directories(
    parallel-bfs-test ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

add_library(bag-lib OBJECT source/bag.cpp)

target_include_directories(
    bag-lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

# target_compile_features(parallel-bfs_lib PUBLIC cxx_std_17)

# ---- Declare executable ----

add_executable(parallel-bfs_exe source/main.cpp)
add_executable(parallel-bfs::exe ALIAS parallel-bfs_exe)

set_property(TARGET parallel-bfs_exe PROPERTY OUTPUT_NAME parallel-bfs)

target_compile_features(parallel-bfs_exe PRIVATE cxx_std_17)

target_link_libraries(parallel-bfs_exe PRIVATE parallel-bfs_lib)

# -------- Parallel BFS Test executable --------
add_executable(parallel-bfs-test_exe source/bfs_main.cpp)
add_executable(parallel-bfs-test::exe ALIAS parallel-bfs-test_exe)

set_property(TARGET parallel-bfs-test_exe PROPERTY OUTPUT_NAME bfs)

target_compile_features(parallel-bfs-test_exe PRIVATE cxx_std_17)
target_link_libraries(parallel-bfs-test_exe PRIVATE parallel-bfs-test)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT parallel-bfs_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of parallel-bfs"
  )
endif()

include(cmake/dev-mode.cmake)
