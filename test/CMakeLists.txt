# Test configuration for roslibcpp

# Find Google Test
find_package(GTest REQUIRED)

# Include directories
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../include)

# Test executable
add_executable(roslibcpp_tests
    test_message.cpp
    test_topic.cpp
    test_service.cpp
    test_param.cpp
    test_time.cpp
    test_ros.cpp
    test_ros2.cpp
)

# Link libraries
target_link_libraries(roslibcpp_tests
    roslibcpp
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    pthread
)

# Add test
add_test(NAME roslibcpp_tests
         COMMAND roslibcpp_tests)

# Individual test targets (optional)
add_executable(test_message test_message.cpp)
target_link_libraries(test_message roslibcpp ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

add_executable(test_topic test_topic.cpp)
target_link_libraries(test_topic roslibcpp ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

add_executable(test_service test_service.cpp)
target_link_libraries(test_service roslibcpp ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

add_executable(test_param test_param.cpp)
target_link_libraries(test_param roslibcpp ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

add_executable(test_time test_time.cpp)
target_link_libraries(test_time roslibcpp ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)