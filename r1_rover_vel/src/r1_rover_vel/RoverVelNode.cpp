
#include "r1_rover_vel/RoverVelNode.hpp"

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "mavros_msgs/msg/position_target.hpp"

namespace r1_rover_vel
{

using std::placeholders::_1;
using namespace std::chrono_literals;


RoverVelNode::RoverVelNode() 
: Node("rover_vel_node")
{
    twist_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "/cmd_vel", 10, std::bind(&RoverVelNode::twist_callback, this, _1));

    position_target_pub_ = this->create_publisher<mavros_msgs::msg::PositionTarget>(
        "/mavros/setpoint_raw/local", 10);

    timer_ = this->create_wall_timer(
        100ms, std::bind(&RoverVelNode::publish_position_target, this));

    RCLCPP_INFO(this->get_logger(), "/cmd_vel -> /mavros/setpoint_raw/local");

    vx_ = 0.0;
    yaw_rate_ = 0.0;
}

void RoverVelNode::twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
{
    vx_ = msg->linear.x;
    yaw_rate_ = msg->angular.z;
}

void RoverVelNode::publish_position_target()
{
    mavros_msgs::msg::PositionTarget msg;

    msg.header.stamp = this->get_clock()->now();

    msg.coordinate_frame = 8;
    msg.type_mask = 1991;

    msg.velocity.x = vx_;
    msg.velocity.y = yaw_rate_;
    msg.velocity.z = 0;

    msg.yaw_rate = yaw_rate_;

    position_target_pub_->publish(msg);
}

}  // namespace r1_rover_vel
