#pragma once

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace rclcpp;

class Listener : public Node {
public:
    Listener();
    ~Listener(){};

private:
    void topicCallback(const std_msgs::msg::String::SharedPtr msg) const;
    Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};
