# Building and Installing roslibcpp

This document provides detailed instructions for building and installing the roslibcpp library from source.

## Prerequisites

Before building roslibcpp, ensure you have the following dependencies installed:

- CMake 3.10 or higher
- A C++ compiler (GCC, Clang, or MSVC)
- JsonCpp library
- Google Test framework (for building tests)

## Building the Library

### Unix/Linux/macOS

1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd roslibcpp
   ```

2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure with CMake:
   ```bash
   cmake ..
   ```

4. Build the library:
   ```bash
   make
   ```

### Windows

1. Clone the repository:
   ```cmd
   git clone <repository_url>
   cd roslibcpp
   ```

2. Create a build directory:
   ```cmd
   mkdir build
   cd build
   ```

3. Configure with CMake:
   ```cmd
   cmake ..
   ```

4. Build the library:
   ```cmd
   cmake --build . --config Release
   ```

## Build Options

The following CMake options are available:

- `BUILD_TESTS` - Build unit tests (default: ON)
- `BUILD_EXAMPLES` - Build example applications (default: ON)
- `BUILD_SHARED_LIBS` - Build shared libraries instead of static (default: OFF)

Example with options:
```bash
cmake .. -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON -DBUILD_SHARED_LIBS=OFF
```

## Running Tests

To run the unit tests after building:

```bash
make test
```

Or run specific test executables:
```bash
./test/roslibcpp_tests
```

## Installing the Library

### Unix/Linux/macOS

After building, install the library using:

```bash
sudo make install
```

This will install:
- Header files to `/usr/local/include/roslibcpp/`
- Library files to `/usr/local/lib/`
- CMake configuration files to `/usr/local/lib/cmake/roslibcpp/`

### Windows

After building, install the library using:

```cmd
cmake --build . --target install --config Release
```

This will install:
- Header files to `C:\Program Files\roslibcpp\include\roslibcpp\`
- Library files to `C:\Program Files\roslibcpp\lib\`
- CMake configuration files to `C:\Program Files\roslibcpp\lib\cmake\roslibcpp\`

## Using the Installed Library

After installation, you can use roslibcpp in your CMake projects by adding:

```cmake
find_package(roslibcpp REQUIRED)
target_link_libraries(your_target roslibcpp::roslibcpp)
```

## Building Examples

The examples can be built separately or together with the library:

```bash
# Build all examples
make

# Build specific example
make chatter
make listener
```

## Troubleshooting

### Common Issues

1. **Missing Dependencies**: Ensure all required dependencies are installed
2. **CMake Configuration Errors**: Clear the build directory and reconfigure
3. **Linking Errors**: Check that all dependencies are properly linked

### Compiler Requirements

- GCC 7.0 or higher
- Clang 6.0 or higher
- MSVC 2017 or higher

### Dependency Installation

#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install cmake build-essential libjsoncpp-dev libgtest-dev
```

#### macOS (with Homebrew):
```bash
brew install cmake jsoncpp googletest
```

#### Windows (with vcpkg):
```cmd
vcpkg install jsoncpp gtest
```