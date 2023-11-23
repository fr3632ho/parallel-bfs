# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(parallel-bfsTests LANGUAGES CXX)

# ---- Tests ----

# add_executable(parallel-bfs_test source/parallel-bfs_test.cpp)
# target_link_libraries(parallel-bfs_test PRIVATE parallel-bfs_lib)
# target_compile_features(parallel-bfs_test PRIVATE cxx_std_17)

# -- bag test --
add_executable(bag_test source/bag_test.cpp)
target_link_libraries(bag_test PRIVATE bag-lib)
# target_compile_features(bag_test PRIVATE cxx_std_17)

# -- pennants test --
add_executable(pennants_test source/pennants_test.cpp)
target_link_libraries(pennants_test PRIVATE bag-lib)
# target_compile_features(pennants_test PRIVATE cxx_std_17)

add_executable(bag_merge_6_and_3 source/bag_merge_6_and_3.cpp)
target_link_libraries(bag_merge_6_and_3 PRIVATE bag-lib)
# target_compile_features(bag_merge_6_and_3  PRIVATE cxx_std_17)

add_executable(bag_merge_373_711 source/bag_merge_373_711.cpp)
target_link_libraries(bag_merge_373_711 PRIVATE bag-lib)

add_executable(bag_merge_1023_1023 source/bag_merge_1023_1023.cpp)
target_link_libraries(bag_merge_1023_1023 PRIVATE bag-lib)

add_executable(bag_merge_1023_1 source/bag_merge_1023_1.cpp)
target_link_libraries(bag_merge_1023_1 PRIVATE bag-lib)

add_executable(pennant_split_64 source/pennant_split_64.cpp)
target_link_libraries(pennant_split_64 PRIVATE bag-lib)

add_executable(bag_split_16 source/bag_split_16.cpp)
target_link_libraries(bag_split_16 PRIVATE bag-lib)

add_executable(bag_split_23 source/bag_split_23.cpp)
target_link_libraries(bag_split_23 PRIVATE bag-lib)

add_executable(bag_split_13 source/bag_split_13.cpp)
target_link_libraries(bag_split_13 PRIVATE bag-lib)

add_executable(bag_split_1023 source/bag_split_1023.cpp)
target_link_libraries(bag_split_1023 PRIVATE bag-lib)

add_executable(bag_merge_split_1023 source/bag_merge_split_1023.cpp)
target_link_libraries(bag_merge_split_1023 PRIVATE bag-lib)

# Iterator test
add_executable(pennant_iterate source/pennant_iterate.cpp)
target_link_libraries(pennant_iterate PRIVATE bag-lib)



# add_test(NAME parallel-bfs_test COMMAND parallel-bfs_test)
add_test(NAME bag_test.cpp COMMAND bag_test)
add_test(NAME pennants_test.cpp COMMAND pennants_test)
add_test(NAME bag_merge_6_and_3.cpp COMMAND bag_merge_6_and_3)
add_test(NAME bag_merge_373_711.cpp COMMAND bag_merge_373_711)
add_test(NAME bag_merge_1023_1023.cpp COMMAND bag_merge_1023_1023)
add_test(NAME bag_merge_1023_1.cpp COMMAND bag_merge_1023_1)
add_test(NAME bag_split_16.cpp COMMAND bag_split_16)
add_test(NAME bag_split_23.cpp COMMAND bag_split_23)
add_test(NAME bag_split_13.cpp COMMAND bag_split_13)
add_test(NAME bag_split_1023.cpp COMMAND bag_split_1023)
add_test(NAME pennant_split_64.cpp COMMAND pennant_split_64)
add_test(NAME bag_merge_split_1023.cpp COMMAND bag_merge_split_1023)
add_test(NAME pennant_iterate.cpp COMMAND pennant_iterate)

# ---- End-of-file commands ----

# --- Multiple tests ---
# create the testing file and list of tests
# set(CMAKE_TESTDRIVER_BEFORE_TESTMAIN "") 
# set(CMAKE_TESTDRIVER_AFTER_TESTMAIN "")

# create_test_sourcelist (Tests
#   CommonCxxTests.cxx
#   bag_merge_6_and_3.cpp
# #   EXTRA_INCLUDE bag-lib
#   )

# # add the executable
# add_executable (CommonCxxTests ${Tests})
# target_link_libraries(CommonCxxTests PRIVATE bag-lib)

# # remove the test driver source file
# set (TestsToRun ${Tests})
# remove (TestsToRun CommonCxxTests.cxx)

# # Add all the ADD_TEST for each test
# foreach (test ${TestsToRun})
#   get_filename_component (TName ${test} NAME_WE)
#   add_test (NAME ${TName} COMMAND CommonCxxTests ${TName})
# endforeach ()

add_folders(test)
