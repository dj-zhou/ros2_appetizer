#pragma once

#include "agv_interfaces/srv/add_three_ints.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/empty.hpp"

using namespace rclcpp;

class Listener : public Node {
public:
    Listener();
    ~Listener(){};

private:
    void topicCallback(const std_msgs::msg::String::SharedPtr msg) const;
    void timerAddCallback();
    void timerCallback();

    TimerBase::SharedPtr timer_;
    TimerBase::SharedPtr timer_add_;
    Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    Client<std_srvs::srv::Empty>::SharedPtr client_;
    Client<agv_interfaces::srv::AddThreeInts>::SharedPtr client_add_;
};
