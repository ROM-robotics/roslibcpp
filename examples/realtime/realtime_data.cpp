#include <roslibcpp/roslibcpp.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <limits>

class RealTimeDataProcessor {
private:
    roslibcpp::Ros ros_;
    
    // Topics for real-time data
    roslibcpp::Topic imu_topic_;
    roslibcpp::Topic scan_topic_;
    roslibcpp::Topic odom_topic_;
    roslibcpp::Topic battery_topic_;
    
    // Performance monitoring
    std::chrono::steady_clock::time_point last_imu_time_;
    std::chrono::steady_clock::time_point last_scan_time_;
    int imu_count_ = 0;
    int scan_count_ = 0;
    
public:
    RealTimeDataProcessor() 
        : ros_("localhost", 9090),
          imu_topic_(&ros_, "/imu/data", "sensor_msgs/Imu"),
          scan_topic_(&ros_, "/scan", "sensor_msgs/LaserScan"),
          odom_topic_(&ros_, "/odom", "nav_msgs/Odometry"),
          battery_topic_(&ros_, "/battery_state", "sensor_msgs/BatteryState") {
    }
    
    bool connect() {
        try {
            std::cout << "Connecting to ROS2..." << std::endl;
            ros_.connect();
            
            if (!ros_.is_connected()) {
                std::cerr << "Failed to connect to ROS2!" << std::endl;
                return false;
            }
            
            std::cout << "Connected to ROS2 successfully!" << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Connection error: " << e.what() << std::endl;
            return false;
        }
    }
    
    void setupSubscriptions() {
        // IMU data subscription
        imu_topic_.subscribe([this](const roslibcpp::Message& msg) {
            auto now = std::chrono::steady_clock::now();
            
            // Calculate frequency
            if (imu_count_ > 0) {
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - last_imu_time_);
                double frequency = 1000000.0 / duration.count();
                std::cout << std::fixed << std::setprecision(1);
                std::cout << "[IMU] Freq: " << frequency << " Hz, ";
            }
            
            last_imu_time_ = now;
            imu_count_++;
            
            // Process IMU data
            double orientation_x = msg["orientation"]["x"].asDouble();
            double orientation_y = msg["orientation"]["y"].asDouble();
            double orientation_z = msg["orientation"]["z"].asDouble();
            
            std::cout << "Orientation: (" << orientation_x << ", " 
                      << orientation_y << ", " << orientation_z << ")" << std::endl;
        });
        
        // Laser scan data subscription
        scan_topic_.subscribe([this](const roslibcpp::Message& msg) {
            auto now = std::chrono::steady_clock::now();
            
            // Calculate frequency
            if (scan_count_ > 0) {
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - last_scan_time_);
                double frequency = 1000000.0 / duration.count();
                std::cout << std::fixed << std::setprecision(1);
                std::cout << "[Scan] Freq: " << frequency << " Hz, ";
            }
            
            last_scan_time_ = now;
            scan_count_++;
            
            // Process laser scan data
            auto ranges = msg["ranges"];
            int num_ranges = ranges.size();
            
            // Calculate basic statistics
            double min_range = std::numeric_limits<double>::max();
            double max_range = 0.0;
            double sum = 0.0;
            
            for (int i = 0; i < num_ranges; ++i) {
                double range = ranges[i].asDouble();
                if (range > 0.0 && range < min_range) min_range = range;
                if (range > max_range) max_range = range;
                sum += range;
            }
            
            double avg_range = sum / num_ranges;
            
            std::cout << "Scan points: " << num_ranges 
                      << ", Range: [" << min_range << ", " << max_range 
                      << "], Avg: " << avg_range << std::endl;
        });
        
        // Odometry data subscription
        odom_topic_.subscribe([this](const roslibcpp::Message& msg) {
            double x = msg["pose"]["pose"]["position"]["x"].asDouble();
            double y = msg["pose"]["pose"]["position"]["y"].asDouble();
            double z = msg["pose"]["pose"]["position"]["z"].asDouble();
            
            std::cout << "[Odometry] Position: (" << x << ", " << y << ", " << z << ")" << std::endl;
        });
        
        // Battery state subscription
        battery_topic_.subscribe([this](const roslibcpp::Message& msg) {
            double voltage = msg["voltage"].asDouble();
            double percentage = msg["percentage"].asDouble();
            
            std::cout << "[Battery] " << percentage << "% (" << voltage << "V)" << std::endl;
        });
    }
    
    void run() {
        std::cout << "Starting real-time data processing..." << std::endl;
        std::cout << "Press Ctrl+C to stop" << std::endl;
        
        try {
            ros_.run_forever();
        } catch (const std::exception& e) {
            std::cerr << "Runtime error: " << e.what() << std::endl;
        }
    }
};

int main() {
    try {
        RealTimeDataProcessor processor;
        
        if (!processor.connect()) {
            return 1;
        }
        
        processor.setupSubscriptions();
        processor.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}