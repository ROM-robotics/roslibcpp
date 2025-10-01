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
        
        // Subscribe to TF messages
        roslibcpp::Topic tf_topic(&ros, "/tf", "tf2_msgs/TFMessage");
        
        // Set up TF callback
        tf_topic.subscribe([](const roslibcpp::Message& msg) {
            auto transforms = msg["transforms"];
            for (int i = 0; i < transforms.size(); ++i) {
                auto transform = transforms[i];
                std::string frame_id = transform["header"]["frame_id"].asString();
                std::string child_frame_id = transform["child_frame_id"].asString();
                
                double x = transform["transform"]["translation"]["x"].asDouble();
                double y = transform["transform"]["translation"]["y"].asDouble();
                double z = transform["transform"]["translation"]["z"].asDouble();
                
                std::cout << "Transform from " << frame_id << " to " << child_frame_id 
                          << ": (" << x << ", " << y << ", " << z << ")" << std::endl;
            }
        });
        
        std::cout << "Listening to TF messages. Press Ctrl+C to exit." << std::endl;
        
        // Run forever
        ros.run_forever();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}