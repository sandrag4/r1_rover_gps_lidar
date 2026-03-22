
#include "rclcpp/rclcpp.hpp"
#include "odom_to_tf/OdomNode.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto nodo = std::make_shared<odom_to_tf::OdomNode>();

    rclcpp::spin(nodo);

    rclcpp::shutdown();
    return 0;
}