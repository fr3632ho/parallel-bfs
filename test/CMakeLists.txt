# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(parallel-bfsTests LANGUAGES CXX)

# ---- Tests ----

add_executable(parallel-bfs_test source/parallel-bfs_test.cpp)
target_link_libraries(parallel-bfs_test PRIVATE parallel-bfs_lib)
target_compile_features(parallel-bfs_test PRIVATE cxx_std_17)

add_test(NAME parallel-bfs_test COMMAND parallel-bfs_test)

# ---- End-of-file commands ----

add_folders(Test)
