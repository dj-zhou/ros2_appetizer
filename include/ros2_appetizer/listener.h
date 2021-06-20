#pragma once

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
    void timerCallback();

    TimerBase::SharedPtr timer_;
    Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    Client<std_srvs::srv::Empty>::SharedPtr client_;
};
