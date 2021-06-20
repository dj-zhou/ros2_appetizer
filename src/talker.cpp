#include "ros2_appetizer/talker.h"

using namespace std::chrono_literals;
using namespace std::placeholders;

Talker::Talker() : Node("talker"), count_(0), talk_style_(true) {
    publisher_ = this->create_publisher<std_msgs::msg::String>("/chatter", 10);
    timer_ =
        this->create_wall_timer(1s, std::bind(&Talker::timerCallback, this));
    service_ = this->create_service<std_srvs::srv::Empty>(
        "/toggle", std::bind(&Talker::serviceCallback, this, _1, _2));
}

void Talker::timerCallback() {
    auto message = std_msgs::msg::String();
    if (talk_style_) {
        message.data = "Hello, ROS2 and AGV! " + std::to_string(count_++);
    }
    else {
        message.data = std::to_string(count_++) + ": It's a good day today!";
    }
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
}

void Talker::serviceCallback(
    const std::shared_ptr<std_srvs::srv::Empty::Request> request,
    std::shared_ptr<std_srvs::srv::Empty::Response> response) {
    ( void )request;
    ( void )response;
    talk_style_ = !talk_style_;
}
