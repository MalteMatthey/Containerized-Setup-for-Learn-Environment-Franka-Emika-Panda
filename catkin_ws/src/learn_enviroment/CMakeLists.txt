cmake_minimum_required(VERSION 3.0.2)
project(learn-enviroment)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  rviz
  moveit_commander
  moveit_msgs
  geometry_msgs
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

catkin_install_python(PROGRAMS
  tasks/exercise_1.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

set(CMAKE_AUTOMOC ON)

## This plugin includes Qt widgets, so we must include Qt.
## We'll use the version that rviz used so they are compatible.
if(rviz_QT_VERSION VERSION_LESS "5")
  message(STATUS "Using Qt4 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt4 ${rviz_QT_VERSION} EXACT REQUIRED QtCore QtGui)
  ## pull in all required include dirs, define QT_LIBRARIES, etc.
  include(${QT_USE_FILE})
else()
  message(STATUS "Using Qt5 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Core Widgets)
  ## make target_link_libraries(${QT_LIBRARIES}) pull in all required dependencies
  set(QT_LIBRARIES Qt5::Widgets)
endif()

add_definitions(-DQT_NO_KEYWORDS)

set(${PROJECT_NAME}_HDRS
  include/${PROJECT_NAME}/rviz_panel.hpp
)

set(${PROJECT_NAME}_SRCS
  src/rviz_panel.cpp
)


set(${PROJECT_NAME}_UIS
  resource/learn_panel.ui
)

# Create header from ui file (uic)
if(rviz_QT_VERSION VERSION_LESS "5")
    message(STATUS "Generate header for ui with rviz_QT_VERSION: ${rviz_QT_VERSION}")
    qt4_wrap_ui(${PROJECT_NAME}_UIS_H ${${PROJECT_NAME}_UIS})
    qt4_wrap_cpp(${PROJECT_NAME}_MOCS ${${PROJECT_NAME}_HDRS})
else()
    message(STATUS "Generate header for ui with rviz_QT_VERSION: ${rviz_QT_VERSION}")
    qt5_wrap_ui(${PROJECT_NAME}_UIS_H ${${PROJECT_NAME}_UIS})
    qt5_wrap_cpp(${PROJECT_NAME}_MOCS ${${PROJECT_NAME}_HDRS})
endif()


add_library(learn_panel
  ${${PROJECT_NAME}_SRCS}
  ${${PROJECT_NAME}_UIS_H}
  ${${PROJECT_NAME}_MOCS} 
)

target_link_libraries(learn_panel
  ${catkin_LIBRARIES}
  ${QT_LIBRARIES}
  ${topic_tools_LIBRARIES}
)