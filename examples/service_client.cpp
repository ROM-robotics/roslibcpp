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
        
        // Create a service client
        roslibcpp::ServiceClient client(&ros, "/add_two_ints", "example_interfaces/srv/AddTwoInts");
        
        // Prepare service request
        roslibcpp::Message request;
        request["a"] = 5;
        request["b"] = 3;
        
        // Call the service
        auto response = client.call(request);
        
        if (response) {
            int sum = (*response)["sum"].asInt();
            std::cout << "Service response: " << sum << std::endl;
        } else {
            std::cerr << "Service call failed!" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}