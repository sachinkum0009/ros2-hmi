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
    }
    void Ros2Hmi::joint1minusCb() {
        qDebug() << "Joint 1 Minus Button clicked!";
    }
    void Ros2Hmi::joint2plusCb() {
        qDebug() << "Joint 2 Plus Button clicked!";
    }

    void Ros2Hmi::joint2minusCb() {
        qDebug() << "Joint 2 Minus Button clicked!";
    }

    void Ros2Hmi::joint3plusCb() {
        qDebug() << "Joint 3 Plus Button clicked!";
    }

    void Ros2Hmi::joint3minusCb() {
        qDebug() << "Joint 3 Minus Button clicked!";
    }

    void Ros2Hmi::joint4plusCb() {
        qDebug() << "Joint 4 Plus Button clicked!";
    }

    void Ros2Hmi::joint4minusCb() {
        qDebug() << "Joint 4 Minus Button clicked!";
    }

    void Ros2Hmi::joint5plusCb() {
        qDebug() << "Joint 5 Plus Button clicked!";
    }

    void Ros2Hmi::joint5minusCb() {
        qDebug() << "Joint 5 Minus Button clicked!";
    }

    void Ros2Hmi::joint6plusCb() {
        qDebug() << "Joint 6 Plus Button clicked!";
    }

    void Ros2Hmi::joint6minusCb() {
        qDebug() << "Joint 6 Minus Button clicked!";
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

}
