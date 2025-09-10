cmake_minimum_required(VERSION 3.20)
project(ros2_hmi)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(control_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(interactive_markers REQUIRED)
find_package(pluginlib REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5UiTools REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(std_srvs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(moveit_ros_planning REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)

include_directories(
  include
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5Quick_INCLUDE_DIRS}
)

# Manually process `ros2_hmi.hpp` for Qt's MOC
qt5_wrap_cpp(MOC_SOURCES include/ros2_hmi/ros2_hmi.hpp)

add_executable(${PROJECT_NAME}_node
  src/ros2_hmi_node.cpp
  src/ros2_hmi.cpp
  ${MOC_SOURCES}  # Ensure MOC-generated files are compiled
)

target_include_directories(${PROJECT_NAME}_node
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>
)


target_link_libraries(${PROJECT_NAME}_node
  Qt5::Core
  Qt5::Quick
  Qt5::Widgets
  Qt5::UiTools
  ament_index_cpp::ament_index_cpp
  rclcpp::rclcpp
  rviz_common::rviz_common
  rviz_default_plugins::rviz_default_plugins
  rviz_rendering::rviz_rendering
)

ament_target_dependencies(${PROJECT_NAME}_node
  control_msgs
  geometry_msgs
  std_msgs
  std_srvs
  moveit_ros_planning
  moveit_ros_planning_interface
)

install(TARGETS ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch ui
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  # Add MoveIt integration test
  ament_add_gtest(test_moveit_integration test/test_moveit_integration.cpp)
  target_include_directories(test_moveit_integration
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )
  ament_target_dependencies(test_moveit_integration
    rclcpp
    moveit_ros_planning_interface
  )
endif()

ament_package()
