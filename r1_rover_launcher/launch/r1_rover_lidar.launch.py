from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    pkg_share = get_package_share_directory('r1_rover_launcher')

    rviz_config = os.path.join(
        pkg_share,
        'rviz',
        'rover_lidar.rviz'
    )

    bridge_config = os.path.join(
        pkg_share,
        'config',
        'r1_rover_bridge.yaml'
    )

    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{'config_file': bridge_config}],
        output='screen'
    )

    base_to_lidar =Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0.13','0','0.13','0','0','0','base_link','rover_lidar_r1_0/lidar_link/gpu_lidar'],
        output='screen'
    )

    base_to_lfwheel = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0.15','0.16317','0.0215','0','0','0','base_link','lf_wheel_link'],
        output='screen'
    )

    base_to_lbwheel = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['-0.15','0.16317','0.0215','0','0','0','base_link','lb_wheel_link'],
        output='screen'
    )

    base_to_rfwheel = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0.15','-0.16317','0.0215','0','0','0','base_link','rf_wheel_link'],
        output='screen'
    )

    base_to_rbwheel = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['-0.15','-0.16317','0.0215','0','0','0','base_link','rb_wheel_link'],
        output='screen'
    )

    rviz = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', rviz_config],
        output='screen'
    )

    return LaunchDescription([
        bridge,
        base_to_lidar,
        base_to_lfwheel,
        base_to_lbwheel,
        base_to_rfwheel,
        base_to_rbwheel,
        rviz
    ])
