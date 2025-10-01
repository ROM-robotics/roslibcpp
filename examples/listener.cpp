#include <roslibcpp/roslibcpp.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    try {
        // Create ROS connection
        roslibcpp::Ros ros("localhost", 9090);
        
        std::cout << "Connecting to ROS..." << std::endl;
        ros.connect();
        
        if (!ros.is_connected()) {
            std::cerr << "Failed to connect to ROS!" << std::endl;
            return 1;
        }
        
        std::cout << "Connected to ROS successfully!" << std::endl;
        
        // Create a subscriber for the chatter topic
        roslibcpp::Topic chatter_topic(&ros, "/chatter", "std_msgs/String");
        
        // Subscribe to messages
        chatter_topic.subscribe([](const roslibcpp::Message& msg) {
            std::string data = msg["data"].asString();
            std::cout << "Received: " << data << std::endl;
        });
        
        std::cout << "Listening to /chatter topic. Press Ctrl+C to exit." << std::endl;
        
        // Run forever
        ros.run_forever();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}