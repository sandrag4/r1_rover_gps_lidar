
#ifndef R1_ROVER_VEL__ROVER_VEL_NODE_HPP_
#define R1_ROVER_VEL__ROVER_VEL_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "mavros_msgs/msg/position_target.hpp"


namespace r1_rover_vel
{

class RoverVelNode : public rclcpp::Node
{
public:
    RoverVelNode();

private:
    void twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg);
    void publish_position_target();

    double vx_;
    double yaw_rate_;

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_sub_;
    rclcpp::Publisher<mavros_msgs::msg::PositionTarget>::SharedPtr position_target_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace r1_rover_vel

#endif  // R1_ROVER_VEL__ROVER_VEL_NODE_HPP_
