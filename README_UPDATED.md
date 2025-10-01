# roslibcpp

A C++ library for interacting with ROS2 Humble via WebSocket, inspired by roslibpy. 

## Features

- Connect to ROS2 Humble through rosbridge
- Subscribe and publish to topics
- Call and advertise services
- Get and set parameters
- Support for JSON message formats        

## Dependencies

- websocketpp
- JsonCpp

## Documentation

For detailed documentation, please see the [docs](docs/) directory:

- [Introduction](docs/introduction.md)
- [Getting Started](docs/getting_started.md)
- [Installation](docs/installation.md)
- [Building and Installation](docs/building_and_installation.md)
- [Real-time Usage](docs/realtime.md)

## Building

### Standard Build
```bash
mkdir build
cd build
cmake ..
make
```

### Qt Integration
For Qt applications, you can integrate roslibcpp as a library:

1. Install dependencies:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install libwebsocketpp-dev libjsoncpp-dev

   # Or using vcpkg
   vcpkg install websocketpp jsoncpp      
   ```

2. Add to your Qt CMakeLists.txt:
   ```cmake
   find_package(websocketpp REQUIRED)     
   find_package(JsonCpp REQUIRED)
   add_subdirectory(roslibcpp) # If included as submodule

   target_link_libraries(your_target roslibcpp)
   ```

## Usage

### Basic Usage
```cpp
#include <roslibcpp/roslibcpp.h>

// Create a ROS connection
roslibcpp::Ros ros("localhost", 9090);

// Connect to ROS
ros.connect();

// Create a topic
roslibcpp::Topic chatter(&ros, "/chatter", "std_msgs/String");

// Subscribe to the topic
chatter.subscribe([](const roslibcpp::Message& msg) {
    std::cout << "Received: " << msg["data"] << std::endl;
});

// Run the event loop
ros.run_forever();
```

### Qt Integration
See examples/qt/ for a complete Qt example application.

## Examples

The library includes several examples in the [examples/](examples/) directory:

- [chatter.cpp](examples/chatter.cpp) - Basic publisher example
- [listener.cpp](examples/listener.cpp) - Basic subscriber example
- [service_client.cpp](examples/service_client.cpp) - Service client example
- [service_server.cpp](examples/service_server.cpp) - Service server example
- [action_client.cpp](examples/action_client.cpp) - Action client example
- [tf_listener.cpp](examples/tf_listener.cpp) - TF listener example
- [realtime/](examples/realtime/) - Real-time data processing example
- [qt/](examples/qt/) - Qt GUI integration example

## Qt Specific Considerations

1. **Threading**: Run roslibcpp in a separate thread to avoid blocking the UI       
2. **Signal-Slot Integration**: Use Qt's signal-slot mechanism to communicate between ROS callbacks and UI updates
3. **Event Loop**: Choose between Qt's event loop and roslibcpp's event loop appropriately

## License

MIT