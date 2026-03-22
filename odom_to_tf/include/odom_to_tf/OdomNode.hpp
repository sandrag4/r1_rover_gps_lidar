
#ifndef ODOM_TO_TF__ODOM_NODE_HPP_
#define ODOM_TO_TF__ODOM_NODE_HPP_


#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"

namespace odom_to_tf
{

class OdomNode : public rclcpp::Node
{
public:
    OdomNode();

private:
    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg);

    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
    
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

}  // namespace odom_to_tf

#endif  // ODOM_TO_TF__ODOM_NODE_HPP_