
#ifndef R1_SIM_VEL__SIM_VEL_NODE_HPP_
#define R1_SIM_VEL__SIM_VEL_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "mavros_msgs/msg/position_target.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"


namespace r1_sim_vel
{

class SimVelNode : public rclcpp::Node
{
public:
    SimVelNode();

private:
    void twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg);
    void laser_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg);
    void publish_position_target();

    double vx_;
    double yaw_rate_;
    double angle_min;
    double angle_max;
    double angle_increment;
    double range_min;
    double range_max;

    int min_idx;
    float distance_min;
    float angle;

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_sub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
    rclcpp::Publisher<mavros_msgs::msg::PositionTarget>::SharedPtr position_target_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace r1_sim_vel

#endif  // R1_SIM_VEL__SIM_VEL_NODE_HPP_
