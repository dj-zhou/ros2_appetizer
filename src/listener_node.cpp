#include "rclcpp/rclcpp.hpp"
#include "ros2_appetizer/listener.h"

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Listener>());
    rclcpp::shutdown();
    return 0;
}
