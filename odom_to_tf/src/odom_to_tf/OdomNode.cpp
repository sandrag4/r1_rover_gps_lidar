
#include "odom_to_tf/OdomNode.hpp"

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"

namespace odom_to_tf
{

using std::placeholders::_1;

OdomNode::OdomNode()
: Node("odom_to_tf_node")
{
    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

    odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>("/mavros/odometry/in", 10,
        std::bind(&OdomNode::odom_callback, this, std::placeholders::_1));

    odom_pub_ = this->create_publisher<nav_msgs::msg::Odometry>("/odom", 10);

    RCLCPP_INFO(this->get_logger(), "TF odom -> base_link");
}

void OdomNode::odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    auto odom_msg = *msg;
    odom_msg.header.stamp = this->get_clock()->now();
    odom_pub_->publish(odom_msg);

    geometry_msgs::msg::TransformStamped t;

    t.header.stamp = this->get_clock()->now();
    
    t.header.frame_id = msg->header.frame_id;   
    t.child_frame_id = msg->child_frame_id;

    t.transform.translation.x = msg->pose.pose.position.x;
    t.transform.translation.y = msg->pose.pose.position.y;
    t.transform.translation.z = msg->pose.pose.position.z;

    t.transform.rotation = msg->pose.pose.orientation;

    tf_broadcaster_->sendTransform(t);
}

}  // namespace odom_to_tf