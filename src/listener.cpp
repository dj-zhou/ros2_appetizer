#include "ros2_appetizer/listener.h"
#include "std_msgs/msg/string.hpp"

using namespace std::placeholders;

Listener::Listener() : Node("listener") {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
        "chatter", 10, std::bind(&Listener::topicCallback, this, _1));
}

void Listener::topicCallback(const std_msgs::msg::String::SharedPtr msg) const {
    RCLCPP_INFO(this->get_logger(), "Received a string: '%s'",
                msg->data.c_str());
}
