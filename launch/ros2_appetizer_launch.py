from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="ros2_appetizer",
            executable="talker",
            name="talker",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"count_start": 50}
            ]
        ),
        Node(
            package="ros2_appetizer",
            executable="listener",
            name="listener",
            output="screen",
            emulate_tty=False,
        )
    ])
