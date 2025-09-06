#pragma once

#include <QApplication>
#include <QFile>
#include <QWidget>
#include <QUiLoader>
#include <QPushButton>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QListView>
#include <QLabel>
#include <iostream>
#include <fstream>

#include <atomic>

#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>

#include <sensor_msgs/msg/joint_state.hpp>


namespace ros2_hmi {
    class Ros2Hmi : public QObject {  // Inherit from QObject
        Q_OBJECT  // Required for signals and slots mechanism
        
    public:
        Ros2Hmi(QApplication &app, std::shared_ptr<rclcpp::Node> node);
        ~Ros2Hmi();
    
    // Move to `slots:` section
    private slots:
        void joint1plusCb();  
        void joint1minusCb();
        void joint2plusCb();
        void joint2minusCb();
        void joint3plusCb();
        void joint3minusCb();
        void joint4plusCb();
        void joint4minusCb();
        void joint5plusCb();
        void joint5minusCb();
        void joint6plusCb();
        void joint6minusCb();


    private:
        void configure_gui();
        void connect_button(const QString &button_name, void (Ros2Hmi::*callback)());

        QUiLoader *loader;
        QFile *file;
        QWidget *widget;
        // QPushButton *joint1Btn, *joint2Btn, *joint3Btn, *joint4Btn, *joint5Btn, *joint6Btn;

        std::shared_ptr<rclcpp::Node> node_;

        std::string package_path_;
        std::thread execution_thread_;
    };
}
