#include "ros2_appetizer/listener.h"
#include "agv_interfaces/srv/add_three_ints.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

Listener::Listener() : Node("listener") {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
        "chatter", 10, std::bind(&Listener::topicCallback, this, _1));
    timer_ =
        this->create_wall_timer(5s, std::bind(&Listener::timerCallback, this));
    timer_add_ = this->create_wall_timer(
        10s, std::bind(&Listener::timerAddCallback, this));
    client_ = this->create_client<std_srvs::srv::Empty>("toggle");
    client_add_ = this->create_client<agv_interfaces::srv::AddThreeInts>(
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
    RCLCPP_INFO(this->get_logger(), "Gets a <std_srvs::srv::Empty> response.");
    ( void )result;
}

void Listener::timerAddCallback() {
    auto request =
        std::make_shared<agv_interfaces::srv::AddThreeInts::Request>();
    RCLCPP_INFO(this->get_logger(),
                "Calls a <agv_interfaces::srv::AddThreeInts> service.");
    request->a = 1;
    request->b = 2;
    request->c = 3;
    while (!client_add_->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                         "Interrupted while waiting for the service. Exiting.");
            return;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                    "service not available, waiting again...");
    }

    auto result = client_add_->async_send_request(request);
    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(),
                                           result)
        == rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld",
                    result.get()->sum);
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                     "Failed to call service add_two_ints");
    }
}
