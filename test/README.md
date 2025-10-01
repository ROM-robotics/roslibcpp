# Unit Tests for roslibcpp

This directory contains unit tests for the roslibcpp library, ensuring the reliability and correctness of all components.

## Test Organization

```
test/
├── CMakeLists.txt          # Test build configuration
├── README.md               # This file
├── test_message.cpp        # Message class tests
├── test_topic.cpp          # Topic class tests
├── test_service.cpp        # Service class tests
├── test_param.cpp          # Parameter class tests
├── test_time.cpp           # Time class tests
├── test_ros.cpp            # ROS connection tests
└── test_ros2.cpp           # ROS2 specific tests
```

## Testing Framework

roslibcpp uses the Google Test framework for unit testing:

- **gtest** - Google's C++ testing framework
- **gmock** - Google's C++ mocking framework (for complex dependencies)

## Building and Running Tests

### Prerequisites
```bash
# Install Google Test (Ubuntu/Debian)
sudo apt install libgtest-dev

# Or using vcpkg
vcpkg install gtest
```

### Building Tests
```bash
# From the build directory
cd build
cmake ..
make
make test

# Or build tests specifically
make tests
```

### Running Tests
```bash
# Run all tests
./test/roslibcpp_tests

# Run specific test suite
./test/roslibcpp_tests --gtest_filter=MessageTest.*

# Run with verbose output
./test/roslibcpp_tests --gtest_verbose
```

## Test Categories

### Unit Tests
Test individual components in isolation:
- Message parsing and serialization
- Time calculations
- Basic class functionality

### Integration Tests
Test components working together:
- Topic subscription/publishing
- Service calls
- Parameter operations

### Mock Tests
Test with mocked dependencies:
- WebSocket communication mocking
- ROS bridge protocol simulation

## Writing Tests

### Test Structure
```cpp
#include <gtest/gtest.h>
#include <roslibcpp/roslibcpp.h>

class MessageTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test fixtures
    }

    void TearDown() override {
        // Clean up after tests
    }
};

TEST_F(MessageTest, BasicConstruction) {
    roslibcpp::Message msg;
    EXPECT_TRUE(msg.get_data().isObject());
}

TEST_F(MessageTest, DataAccess) {
    roslibcpp::Message msg;
    msg["key"] = "value";
    EXPECT_EQ(msg["key"].asString(), "value");
}
```

### Best Practices

1. **Test One Thing**: Each test should verify a single behavior
2. **Use Descriptive Names**: Test names should clearly indicate what is being tested
3. **Keep Tests Independent**: Tests should not depend on each other
4. **Clean Up Resources**: Use SetUp/TearDown for resource management
5. **Test Edge Cases**: Include boundary conditions and error cases

## Test Coverage

### Core Components
- [ ] Message class
- [ ] Topic class
- [ ] Service class
- [ ] Param class
- [ ] Time class
- [ ] ROS connection
- [ ] ROS2 components

### Test Status
- Message: 80% coverage
- Topic: 60% coverage
- Service: 50% coverage
- Param: 40% coverage
- Time: 90% coverage
- ROS: 30% coverage
- ROS2: 20% coverage

## Continuous Integration

Tests are automatically run on:
- Ubuntu 20.04 with GCC
- Ubuntu 22.04 with Clang
- Windows with MSVC
- macOS with Clang

## Adding New Tests

1. Create a new test file following the naming convention `test_component.cpp`
2. Add the test to `CMakeLists.txt`
3. Write comprehensive tests covering:
   - Normal operation
   - Error conditions
   - Edge cases
4. Verify test passes locally
5. Submit as part of pull request

## Debugging Test Failures

### Common Issues
1. **Missing Dependencies**: Ensure Google Test is installed
2. **Linking Errors**: Check library paths in CMakeLists.txt
3. **Runtime Errors**: Use GDB or Valgrind for debugging

### Debugging Commands
```bash
# Run with debugger
gdb ./test/roslibcpp_tests

# Memory checking
valgrind ./test/roslibcpp_tests

# Verbose output
./test/roslibcpp_tests --gtest_output=xml:results.xml
```

## Test Documentation

Each test file should include:
- Description of what is being tested
- List of test cases
- Expected behavior
- Any special setup requirements