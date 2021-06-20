#pragma once

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/empty.hpp"

using namespace rclcpp;

class Talker : public Node {
public:
    Talker();
    ~Talker(){};

private:
    void timerCallback();
    void serviceCallback(
        const std::shared_ptr<std_srvs::srv::Empty::Request> request,
        std::shared_ptr<std_srvs::srv::Empty::Response> response);

    TimerBase::SharedPtr timer_;
    Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    Service<std_srvs::srv::Empty>::SharedPtr service_;
    size_t count_;
    bool talk_style_;
};
