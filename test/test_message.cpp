#include <roslibcpp/message.h>
#include <json/json.h>

// Simple test function for Message class
int test_message_basic() {
    roslibcpp::Message msg;
    return msg.get_data().isObject() ? 0 : 1;
}

int test_message_json() {
    Json::Value test_data;
    test_data["key"] = "value";
    test_data["number"] = 42;
    
    roslibcpp::Message msg(test_data);
    return (msg.get_data()["key"].asString() == "value" && 
            msg.get_data()["number"].asInt() == 42) ? 0 : 1;
}

int main() {
    // Placeholder for Message tests
    return 0;
}