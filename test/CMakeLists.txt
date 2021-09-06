find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable( Test 
  test.cpp 
  ../src/utils.cpp
  ../src/Parameters.cpp
)
target_link_libraries(Test ${GTEST_LIBRARIES} pthread)
