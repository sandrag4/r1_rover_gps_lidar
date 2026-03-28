
#include "rclcpp/rclcpp.hpp"
#include "r1_rover_vel/RoverVelNode.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto nodo = std::make_shared<r1_rover_vel::RoverVelNode>();

    rclcpp::spin(nodo);

    rclcpp::shutdown();
    return 0;
}
