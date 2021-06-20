#include "rclcpp/rclcpp.hpp"
#include "ros2_appetizer/talker.h"

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Talker>());
    rclcpp::shutdown();
    return 0;
}
