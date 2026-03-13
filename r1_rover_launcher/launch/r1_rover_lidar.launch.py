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

    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
            '/scan@sensor_msgs/msg/LaserScan@gz.msgs.LaserScan',
            '/world/urjc_trains_world/model/rover_lidar_r1_0/link/base_link/sensor/navsat_sensor/navsat@sensor_msgs/msg/NavSatFix@gz.msgs.NavSat'
        ],
        remappings=[
            ('/world/urjc_trains_world/model/rover_lidar_r1_0/link/base_link/sensor/navsat_sensor/navsat','/gps')
        ],
        output='screen'
    )

    lidar_tf = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=[
            '0', '0', '0.13',
            '0', '0', '0',
            'base_link',
            'rover_lidar_r1_0/lidar_link/gpu_lidar'
        ],
        output='screen'
    )

    map_to_odom = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=[
            '0', '0', '0',
            '0', '0', '0',
            'map',
            'odom'
        ],
        output='screen'
    )

    odom_to_base = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=[
            '0', '0', '0',
            '0', '0', '0',
            'odom',
            'base_link'
        ],
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
        lidar_tf,
        map_to_odom,
        odom_to_base,
        rviz
    ])

