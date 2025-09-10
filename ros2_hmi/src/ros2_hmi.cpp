#include "ros2_hmi/ros2_hmi.hpp"

namespace ros2_hmi {
    Ros2Hmi::Ros2Hmi(QApplication &app, std::shared_ptr<rclcpp::Node> node) : node_(node)
    {
        (void)app; // Mark 'app' as unused to avoid compiler warning

        try
        {
            package_path_ = ament_index_cpp::get_package_share_directory("ros2_hmi");
            RCLCPP_INFO(node_->get_logger(), "Package path: %s", package_path_.c_str());
        }
        catch(const std::exception &e)
        {
            RCLCPP_ERROR(node_->get_logger(), "Failed to get package share directory: %s", e.what());
            exit(1);
        }

        // Initialize MoveIt move group interface
        try {
            move_group_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(node_, planning_group_);
            RCLCPP_INFO(node_->get_logger(), "MoveIt move group interface initialized for group: %s", planning_group_.c_str());
            
            // Get current joint positions
            current_joint_positions_ = move_group_->getCurrentJointValues();
            RCLCPP_INFO(node_->get_logger(), "Current joint positions retrieved, count: %zu", current_joint_positions_.size());
        }
        catch(const std::exception &e) {
            RCLCPP_ERROR(node_->get_logger(), "Failed to initialize MoveIt interface: %s", e.what());
            // Initialize with default positions if MoveIt fails
            current_joint_positions_.resize(6, 0.0);
        }

    loader = new QUiLoader(widget); // Set parent to widget
    file = new QFile(QString::fromStdString(package_path_ + "/ui/ros2_hmi.ui"), widget); // Set parent to widget
        file->open(QFile::ReadOnly);
        widget = loader->load(file, nullptr);
        file->close();
        
        if (!widget) {
            qDebug() << "Failed to load UI!";
        }

        configure_gui();

        widget->show();
    }
    
    Ros2Hmi::~Ros2Hmi() {
    if (!loader->parent()) delete loader;
    if (!file->parent()) delete file;
    }

    
    void Ros2Hmi::joint1plusCb() {
        qDebug() << "Joint 1 Plus Button clicked!";
        moveJoint(0, joint_increment_);
    }
    void Ros2Hmi::joint1minusCb() {
        qDebug() << "Joint 1 Minus Button clicked!";
        moveJoint(0, -joint_increment_);
    }
    void Ros2Hmi::joint2plusCb() {
        qDebug() << "Joint 2 Plus Button clicked!";
        moveJoint(1, joint_increment_);
    }

    void Ros2Hmi::joint2minusCb() {
        qDebug() << "Joint 2 Minus Button clicked!";
        moveJoint(1, -joint_increment_);
    }

    void Ros2Hmi::joint3plusCb() {
        qDebug() << "Joint 3 Plus Button clicked!";
        moveJoint(2, joint_increment_);
    }

    void Ros2Hmi::joint3minusCb() {
        qDebug() << "Joint 3 Minus Button clicked!";
        moveJoint(2, -joint_increment_);
    }

    void Ros2Hmi::joint4plusCb() {
        qDebug() << "Joint 4 Plus Button clicked!";
        moveJoint(3, joint_increment_);
    }

    void Ros2Hmi::joint4minusCb() {
        qDebug() << "Joint 4 Minus Button clicked!";
        moveJoint(3, -joint_increment_);
    }

    void Ros2Hmi::joint5plusCb() {
        qDebug() << "Joint 5 Plus Button clicked!";
        moveJoint(4, joint_increment_);
    }

    void Ros2Hmi::joint5minusCb() {
        qDebug() << "Joint 5 Minus Button clicked!";
        moveJoint(4, -joint_increment_);
    }

    void Ros2Hmi::joint6plusCb() {
        qDebug() << "Joint 6 Plus Button clicked!";
        moveJoint(5, joint_increment_);
    }

    void Ros2Hmi::joint6minusCb() {
        qDebug() << "Joint 6 Minus Button clicked!";
        moveJoint(5, -joint_increment_);
    }

    void Ros2Hmi::configure_gui() {
        connect_button("joint1plus", &Ros2Hmi::joint1plusCb);
        connect_button("joint1minus", &Ros2Hmi::joint1minusCb);
        connect_button("joint2plus", &Ros2Hmi::joint2plusCb);
        connect_button("joint2minus", &Ros2Hmi::joint2minusCb);
        connect_button("joint3plus", &Ros2Hmi::joint3plusCb);
        connect_button("joint3minus", &Ros2Hmi::joint3minusCb);
        connect_button("joint4plus", &Ros2Hmi::joint4plusCb);
        connect_button("joint4minus", &Ros2Hmi::joint4minusCb);
        connect_button("joint5plus", &Ros2Hmi::joint5plusCb);
        connect_button("joint5minus", &Ros2Hmi::joint5minusCb);
        connect_button("joint6plus", &Ros2Hmi::joint6plusCb);
        connect_button("joint6minus", &Ros2Hmi::joint6minusCb);
    }

    void Ros2Hmi::connect_button(const QString &button_name, void (Ros2Hmi::*callback)()) {
        QPushButton *button = widget->findChild<QPushButton*>(button_name);
        if (button) {
            QObject::connect(button, &QPushButton::clicked, this, callback);
        } else {
            qDebug() << button_name << " not found!";
        }
    }

    void Ros2Hmi::moveJoint(int joint_index, double increment) {
        if (!move_group_) {
            RCLCPP_ERROR(node_->get_logger(), "MoveIt move group not initialized");
            return;
        }

        if (joint_index < 0 || joint_index >= static_cast<int>(current_joint_positions_.size())) {
            RCLCPP_ERROR(node_->get_logger(), "Invalid joint index: %d", joint_index);
            return;
        }

        // Update the target joint position
        current_joint_positions_[joint_index] += increment;
        
        RCLCPP_INFO(node_->get_logger(), "Moving joint %d by %f rad to position %f", 
                   joint_index, increment, current_joint_positions_[joint_index]);

        // Execute the movement
        executeMovement();
    }

    void Ros2Hmi::executeMovement() {
        if (!move_group_) {
            RCLCPP_ERROR(node_->get_logger(), "MoveIt move group not initialized");
            return;
        }

        try {
            // Set the joint value target
            move_group_->setJointValueTarget(current_joint_positions_);
            
            // Plan and execute the movement
            moveit::planning_interface::MoveGroupInterface::Plan plan;
            bool success = (move_group_->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);
            
            if (success) {
                RCLCPP_INFO(node_->get_logger(), "Planning successful, executing movement...");
                auto result = move_group_->execute(plan);
                if (result == moveit::core::MoveItErrorCode::SUCCESS) {
                    RCLCPP_INFO(node_->get_logger(), "Movement executed successfully");
                } else {
                    RCLCPP_ERROR(node_->get_logger(), "Failed to execute movement");
                    // Revert to previous joint positions on failure
                    current_joint_positions_ = move_group_->getCurrentJointValues();
                }
            } else {
                RCLCPP_ERROR(node_->get_logger(), "Failed to plan movement");
                // Revert to previous joint positions on failure
                current_joint_positions_ = move_group_->getCurrentJointValues();
            }
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(node_->get_logger(), "Exception during movement execution: %s", e.what());
            // Revert to previous joint positions on failure
            if (move_group_) {
                current_joint_positions_ = move_group_->getCurrentJointValues();
            }
        }
    }

}
