#include "ros2_hmi/ros2_hmi.hpp"

int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("ros2_hmi_node");

    // Start ROS 2 spinning in a separate thread
    std::thread ros_spin_thread([node]() {
        rclcpp::spin(node);
        rclcpp::shutdown();
    });

    QApplication app(argc, argv);
    ros2_hmi::Ros2Hmi ros2Hmi(app, node);
    return app.exec();
}
