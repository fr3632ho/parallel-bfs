# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(parallel-bfsTests LANGUAGES CXX)

# ---- Tests ----

add_executable(parallel-bfs_test source/parallel-bfs_test.cpp)
target_link_libraries(parallel-bfs_test PRIVATE parallel-bfs_lib)
target_compile_features(parallel-bfs_test PRIVATE cxx_std_17)

# -- bag test --
add_executable(bag_test source/bag_test.cpp)
target_link_libraries(bag_test PRIVATE bag-lib)
target_compile_features(bag_test PRIVATE cxx_std_17)

# -- pennants test --
add_executable(pennants_test source/pennants_test.cpp)
target_link_libraries(pennants_test PRIVATE bag-lib)
target_compile_features(pennants_test PRIVATE cxx_std_17)

add_test(NAME parallel-bfs_test COMMAND parallel-bfs_test)
add_test(NAME bag_test.cpp COMMAND bag_test)
add_test(NAME pennants_test.cpp COMMAND pennants_test)

# ---- End-of-file commands ----

add_folders(test)
