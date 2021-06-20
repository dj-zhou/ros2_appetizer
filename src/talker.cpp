#include "ros2_appetizer/talker.h"

using namespace std::chrono_literals;

Talker::Talker() : Node("talker"), count_(0) {
    publisher_ = this->create_publisher<std_msgs::msg::String>("/chatter", 10);
    timer_ =
        this->create_wall_timer(1s, std::bind(&Talker::timerCallback, this));
}

void Talker::timerCallback() {
    auto message = std_msgs::msg::String();
    message.data = "Hello, ROS2 and AGV! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
}
