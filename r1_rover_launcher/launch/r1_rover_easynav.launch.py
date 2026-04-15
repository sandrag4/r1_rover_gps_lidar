from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
import launch_ros.descriptions
import os

def generate_launch_description():

    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    pkg_share = get_package_share_directory('r1_rover_launcher')

    easynav_config = os.path.join(
        get_package_share_directory('r1_rover_launcher'),
        'config',
        'r1_rover_gps_lidar_navmap.params.yaml'
    )

    gps_rviz_config = os.path.join(
        pkg_share,
        'rviz',
        'gps.rviz'
    )

    easynav_rviz_config = os.path.join(
        pkg_share,
        'rviz',
        'navmap.rviz'
    )

    easynav_cmd = Node(
        package='easynav_system',
        executable='system_main',
        parameters=[easynav_config],
        output='screen'
    )

    gps_rviz = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', gps_rviz_config],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    easynav_rviz = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', easynav_rviz_config],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    offboard_cmd = ExecuteProcess(
        cmd=[
            'ros2', 'service', 'call',
            '/mavros/set_mode',
            'mavros_msgs/srv/SetMode',
            '{base_mode: 0, custom_mode: OFFBOARD}'
        ],
        output='screen'
    )

    arm_cmd = ExecuteProcess(
        cmd=[
            'ros2', 'service', 'call',
            '/mavros/cmd/arming',
            'mavros_msgs/srv/CommandBool',
            '{value: true}'
        ],
        output='screen'
    )

    return LaunchDescription([
        easynav_cmd,
        gps_rviz,
        easynav_rviz,
        offboard_cmd,
        arm_cmd
    ])
