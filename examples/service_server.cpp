#include <roslibcpp/roslibcpp.h>
#include <iostream>
#include <thread>
#include <chrono>

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
        
        // Create a service server
        roslibcpp::ServiceServer server(&ros, "/add_two_ints", "example_interfaces/srv/AddTwoInts");
        
        // Set up service callback
        server.advertise([](const roslibcpp::Message& request) -> roslibcpp::Message {
            int a = request["a"].asInt();
            int b = request["b"].asInt();
            
            roslibcpp::Message response;
            response["sum"] = a + b;
            
            std::cout << "Service called with a=" << a << ", b=" << b << std::endl;
            
            return response;
        });
        
        std::cout << "Service server running. Press Ctrl+C to exit." << std::endl;
        
        // Run forever
        ros.run_forever();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}