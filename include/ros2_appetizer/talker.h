#pragma once

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace rclcpp;

class Talker : public Node {
public:
    Talker();
    ~Talker(){};

private:
    void timerCallback();

    TimerBase::SharedPtr timer_;
    Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};
