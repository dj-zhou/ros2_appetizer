#include "ros2_appetizer/listener.h"

using namespace std::chrono_literals;
using namespace std::placeholders;

Listener::Listener() : Node("listener") {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
        "chatter", 10, std::bind(&Listener::topicCallback, this, _1));
    timer_ =
        this->create_wall_timer(5s, std::bind(&Listener::timerCallback, this));
    timer_add_ = this->create_wall_timer(
        5s, std::bind(&Listener::timerAddCallback, this));
    client_     = this->create_client<std_srvs::srv::Empty>("toggle");
    client_add_ = this->create_client<ros2_appetizer::srv::AddThreeInts>(
        "add_three_ints");
}

void Listener::topicCallback(const std_msgs::msg::String::SharedPtr msg) const {
    RCLCPP_INFO(this->get_logger(), "Received a string: '%s'",
                msg->data.c_str());
}

void Listener::timerCallback() {
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    RCLCPP_INFO(this->get_logger(), "Calls a <std_srvs::srv::Empty> service.");
    auto result = client_->async_send_request(request);
    RCLCPP_INFO(this->get_logger(), "got a response?");
    ( void )result;
}

void Listener::timerAddCallback() {
    auto request =
        std::make_shared<ros2_appetizer::srv::AddThreeInts::Request>();
    RCLCPP_INFO(this->get_logger(), "Calls a <srv::AddThreeInts> service.");
    request->a  = 1;
    request->b  = 2;
    request->c  = 3;
    auto result = client_add_->async_send_request(request);
    RCLCPP_INFO(rclcpp::get_logger(), "Sum: %ld", result.get()->sum);
}
