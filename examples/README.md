# roslibcpp Examples

This directory contains various examples demonstrating how to use the roslibcpp library.

## Basic Examples

### chatter.cpp
Simple publisher example that sends messages to the "/chatter" topic.

### listener.cpp
Simple subscriber example that listens to messages on the "/chatter" topic.

### service_client.cpp
Example showing how to create a service client that calls a remote service.

### service_server.cpp
Example showing how to create a service server that responds to service requests.

### action_client.cpp
Example showing how to create an action client that sends goals and receives results.

### tf_listener.cpp
Example showing how to subscribe to TF transform messages.

## Advanced Examples

### realtime/
Real-time data processing example with multiple topic subscriptions and performance monitoring.

### qt/
Qt GUI integration example showing how to use roslibcpp in a Qt application.

## Building Examples

To build all examples:

```bash
cd build
cmake ..
make
```

To build a specific example:

```bash
cd build
cmake ..
make chatter
make listener
# etc.
```

## Running Examples

Make sure you have a ROS bridge server running before executing the examples:

```bash
# In a separate terminal
ros2 run rosbridge_server rosbridge_websocket
```

Then run the examples:

```bash
./examples/chatter
./examples/listener
# etc.
```