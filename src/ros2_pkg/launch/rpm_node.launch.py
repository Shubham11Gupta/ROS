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
        ExecuteProcess(
            cmd=['ros2','topic','list'],
            output='screen'
        )
    ])