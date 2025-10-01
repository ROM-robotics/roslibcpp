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
        
        // Create an action client
        roslibcpp::ActionClient client(&ros, "/fibonacci", "action_tutorials_interfaces/action/Fibonacci");
        
        // Send a goal
        roslibcpp::Message goal;
        goal["order"] = 10;
        
        // Send goal and wait for result
        auto result = client.send_goal(goal);
        
        if (result) {
            auto sequence = (*result)["sequence"];
            std::cout << "Result sequence: [";
            for (int i = 0; i < sequence.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << sequence[i].asInt();
            }
            std::cout << "]" << std::endl;
        } else {
            std::cerr << "Action failed!" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}