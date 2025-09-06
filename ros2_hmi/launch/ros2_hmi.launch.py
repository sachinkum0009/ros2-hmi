import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    ld = LaunchDescription()

    node = Node(
        package="ros2_hmi",
        name="ros2_hmi_node",
        executable="ros2_hmi_node",
        output="screen",
    )

    ld.add_action(node)
    return ld
