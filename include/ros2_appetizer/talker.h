#pragma once

#include "agv_interfaces/srv/add_three_ints.hpp"
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
    void serviceAddCallback(
        const std::shared_ptr<agv_interfaces::srv::AddThreeInts::Request>
            request,
        std::shared_ptr<agv_interfaces::srv::AddThreeInts::Response> response);
    TimerBase::SharedPtr timer_;
    Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    Service<std_srvs::srv::Empty>::SharedPtr service_;
    Service<agv_interfaces::srv::AddThreeInts>::SharedPtr service_add_;
    size_t count_;
    bool talk_style_;
    int count_start_;
};
