#include "ros2_appetizer/talker.h"
#include "agv_interfaces/srv/add_three_ints.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

Talker::Talker() : Node("talker"), count_(0), talk_style_(true) {
    this->declare_parameter<int>("count_start", 0);
    publisher_ = this->create_publisher<std_msgs::msg::String>("/chatter", 10);
    timer_ =
        this->create_wall_timer(1s, std::bind(&Talker::timerCallback, this));
    service_ = this->create_service<std_srvs::srv::Empty>(
        "/toggle", std::bind(&Talker::serviceCallback, this, _1, _2));
    service_add_ = this->create_service<agv_interfaces::srv::AddThreeInts>(
        "add_three_ints", std::bind(&Talker::serviceAddCallback, this, _1, _2));
}

void Talker::timerCallback() {
    auto message = std_msgs::msg::String();
    this->get_parameter("count_start", count_start_);
    if (talk_style_) {
        message.data =
            "Hello, ROS2 and AGV! " + std::to_string(count_start_ + count_++);
    }
    else {
        message.data = std::to_string(count_start_ + count_++)
                       + ": It's a good day today!";
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

void Talker::serviceAddCallback(
    const std::shared_ptr<agv_interfaces::srv::AddThreeInts::Request> request,
    std::shared_ptr<agv_interfaces::srv::AddThreeInts::Response> response) {
    RCLCPP_INFO(this->get_logger(), "serviceAddCallback: receive a request");
    response->sum = request->a + request->b + request->c;
    RCLCPP_INFO(this->get_logger(), "serviceAddCallback: response");
}
