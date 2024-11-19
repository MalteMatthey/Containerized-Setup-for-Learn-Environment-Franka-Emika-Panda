cmake_minimum_required(VERSION 3.0.2)
project(learn-enviroment)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  rviz
  pluginlib
  std_msgs
  topic_tools
)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  /usr/include/nlohmann
)

set(CMAKE_AUTOMOC ON)