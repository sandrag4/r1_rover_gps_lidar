
#include "rclcpp/rclcpp.hpp"
#include "r1_sim_vel/SimVelNode.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto nodo = std::make_shared<r1_sim_vel::SimVelNode>();

    rclcpp::spin(nodo);

    rclcpp::shutdown();
    return 0;
}
