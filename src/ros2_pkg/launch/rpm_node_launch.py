from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

def generate_launch_description():
    return LaunchDescription([
        Node(
            package = "ros2_pkg",
            executable = "rpm_publisher",
            name = "RPM_pub_nodes",
            parameters = [
                {"rpm_val": 125}
            ]
        ),
        Node(
            package = "ros2_pkg",
            executable = "rpm_subscriber",
            name = "RPM_sub_node",
            parameters = [
                {"radius": 12.5}
            ]
        ),
        Node(
            package = "ros2_pkg",
            executable = "speed_subscriber",
            name = "Speed_sub_node",
            output = 'screen'
        ),
        ExecuteProcess(
            cmd=['ros2','topic','list'],
            output='screen'
        )
    ])