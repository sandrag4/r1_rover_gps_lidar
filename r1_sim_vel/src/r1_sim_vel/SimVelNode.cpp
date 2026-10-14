
#include "r1_sim_vel/SimVelNode.hpp"

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "mavros_msgs/msg/position_target.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

namespace r1_sim_vel
{

using std::placeholders::_1;
using namespace std::chrono_literals;


SimVelNode::SimVelNode() 
: Node("sim_vel_node")
{
  twist_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 10, std::bind(&SimVelNode::twist_callback, this, _1));

  laser_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "/scan", 10, std::bind(&SimVelNode::laser_callback, this, _1));

  position_target_pub_ = this->create_publisher<mavros_msgs::msg::PositionTarget>(
      "/mavros/setpoint_raw/local", 10);

  timer_ = this->create_wall_timer(
      100ms, std::bind(&SimVelNode::publish_position_target, this));

  RCLCPP_INFO(this->get_logger(), "/cmd_vel -> /mavros/setpoint_raw/local");

  vx_ = 0.0;
  yaw_rate_ = 0.0;

  angle_min = -2.641590118408203;
  angle_max = 2.641590118408203;
  angle_increment = 0.007347955368459225;
  range_min = 0.11999999731779099;
  range_max = 20.0;

  min_idx = 0;
  distance_min = 3.0;
  angle = 0.0;
}

void SimVelNode::twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
{
    vx_ = msg->linear.x;
    yaw_rate_ = msg->angular.z;
}

void SimVelNode::laser_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
  angle_min = msg->angle_min;
  angle_max = msg->angle_max;
  angle_increment = msg->angle_increment;
  range_min = msg->range_min;
  range_max = msg->range_max;

  min_idx = std::min_element(msg->ranges.begin(), msg->ranges.end()) - msg->ranges.begin();
  distance_min = msg->ranges[min_idx];

  if (distance_min < 1.5) {
    angle = msg->angle_min + msg->angle_increment * min_idx;
    while (angle > M_PI) {angle -= 2.0 * M_PI;}
    while (angle < -M_PI) {angle += 2.0 * M_PI;}
  } 
}

void SimVelNode::publish_position_target()
{
  mavros_msgs::msg::PositionTarget msg;

  msg.header.stamp = this->get_clock()->now();

  msg.coordinate_frame = 8;
  msg.type_mask = 1991;

  msg.velocity.z = 0;

  msg.yaw_rate = 0.1;

  
  if (distance_min < 1.5 && angle < 0.8 && angle > -0.8) {
    msg.velocity.x = 0.0;
    if (angle > 0.0) {
      msg.velocity.y = -0.1;
    } else {
      msg.velocity.y = 0.1;
    }
    
  } else {
    msg.velocity.x = vx_;
    msg.velocity.y = yaw_rate_;
  }

  position_target_pub_->publish(msg);

}

}  // namespace r1_sim_vel



