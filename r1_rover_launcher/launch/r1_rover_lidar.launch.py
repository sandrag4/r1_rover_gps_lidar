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

    robot_rover_content = Command([
        PathJoinSubstitution([FindExecutable(name="xacro")]),
        " ",
        PathJoinSubstitution([FindPackageShare("r1_description"), "robots", "robot.urdf.xacro"])
    ])

    robot_rover_param = launch_ros.descriptions.ParameterValue(
        robot_rover_content,
        value_type=str
    )


    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{'config_file': bridge_config}, {'use_sim_time': use_sim_time}],
        output='screen'
    )

    base_to_lidar =Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0.13','0','0.13','0','0','0','base_link','rover_lidar_r1_0/lidar_link/gpu_lidar'],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    base_to_lfwheel = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0.15','0.16317','0.0215','0','0','0','base_link','lf_wheel_link'],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    base_to_lbwheel = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['-0.15','0.16317','0.0215','0','0','0','base_link','lb_wheel_link'],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    base_to_rfwheel = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0.15','-0.16317','0.0215','0','0','0','base_link','rf_wheel_link'],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    base_to_rbwheel = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['-0.15','-0.16317','0.0215','0','0','0','base_link','rb_wheel_link'],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    odom_to_tf_cmd = Node(
        package='odom_to_tf',
        executable='odom_to_tf_main',
        name='odom_to_tf',
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    rover_description = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0.0','0.0','0.0','0','0','0','base_link','base_footprint'],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
            'robot_description': robot_rover_param,
        }]
    )
    
    rviz = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', rviz_config],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )


    return LaunchDescription([
        bridge,
        base_to_lidar,
        #base_to_lfwheel,
        #base_to_lbwheel,
        #base_to_rfwheel,
        #base_to_rbwheel,
        odom_to_tf_cmd,
        robot_state_publisher_node,
        rover_description,
        rviz
    ])
