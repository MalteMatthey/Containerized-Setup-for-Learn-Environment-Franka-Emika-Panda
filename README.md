# ROSNoeticStandardContainer

This is a visual studio code development container with ros noetic installed to control a Franka Panda Robot in a simulation and real environment. 

Install Visual studio code with the remote container extension, clone this repository and enjoy a container with everything for ROS and Panda installed. 

## Version

ROS: noetic


Robots: 
 - Panda

 Features:

 - ROS Noetic
 - Ros für Franka Panda
 - MoveIt vorkompiliert



## Installation

### local Windows installation
1. [Visual Studio Code](https://code.visualstudio.com/docs/remote/containers)
1. [WSL](https://learn.microsoft.com/de-de/windows/wsl/install)
2. [Docker](https://docs.docker.com/desktop/install/windows-install/)

    (sometimes you have to install with `pip install docker-compose` [docker-compose](https://docs.docker.com/compose/) as well)
3. Create a fork of this repository.
4. Clone the Repository in your WSL environment (`git clone ...`)
5. Open the repository with `code .` in the repository folder.
6. Use `ctrl + shift + p` *Remote-Containers: Open in Container* to open the container in a docker environment. You have now all the necessary Tools installed.

### on a linux computer (or the computer connected to the real robot)

1. Create a fork of this repository.
2. Clone the Repository in your WSL environment `git clone ...`
3. Open the repository with `code .` in the repository folder.
4. Use `ctrl + shift + p` *Remote-Containers: Open in Container* to open the container in a docker environment. You have now all the necessary Tools installed.

### Functions:

#### Desktop Environment
Go to: [http://localhost:6080/](http://localhost:6080/) in your browser. The Password: "vscode" opens a desktop environment of the container in your browser. All windows you open in the container are shown here.

<img src="/screenshots/webdesktopenvironment.png"  width="300" height="300">


#### Control the real Panda
Remember to activate the panda FCI in the DESK environment with "Activate FCI" and the robot leds should be blue.

##### MoveIt Position Controller
execute: 

    roslaunch panda_moveit_config franka_control.launch robot_ip:=172.16.0.2

This opens the control node of the panda. You can now use the main functions of the panda with access to moveit and the ability to send the robot to x,y,z coordinates. In the [desktop environment](#### Desktop Environment) you can use RVIZ and MoveIT to send the robot to coordinates.

If you move the robot with your hand or the robot was reaching a difficult edge position and won't move further you can recover the robot with: 


    rostopic pub -1 /franka_control/error_recovery/goal franka_msgs/ErrorRecoveryActionGoal "{}"


##### cartesian impedance controller


    roslaunch franka_example_controllers cartesian_impedance_example_controller.launch robot_ip:=172.16.0.2

opens the robot control with RVIZ and a cartesian impedance controller. You can move the robot in RVIZ in the [desktop environment](#### Desktop Environment). 

#### Panda Gazebo (Simulation)

##### cartesian impedance controller


    roslaunch franka_gazebo panda.launch x:=-0.5 \
    world:=$(rospack find franka_gazebo)/world/stone.sdf \
    controller:=cartesian_impedance_example_controller \
    rviz:=true

opens RVIZ and gazebo with a simulation of the panda robot with a cartesian impedance controller. All ROSTopics are loaded to control the virtual robot.

![Gazebo RVIZ Sim](/screenshots/gazebocartesianrvizsim.png "Gazebo RVIZ Sim")

##### moveit position controller

    roslaunch panda_moveit_config demo_gazebo.launch rviz_tutorial:=true

opens RVIZ and gazebo with a simulation of the panda robot with a moveit position controller. You can now add a motion planner in RVIZ if you want. But all move_group topics to control the robot are now started.


### Create a own package/node: 

to create a own ROS Package you create a catkin package in /workspace/catkin_ws/src. You can also clone another ROS package in and work with this. [create a ROS Package](http://wiki.ros.org/ROS/Tutorials/CreatingPackage)

You compile the workspace With `catkin_make` in /workspace/catkin_ws. To use the compiled functions source the workspace setup.bash with `source /workspace/catkin_ws/devel/setup.bash`.


## Errorhandling:

### problems while cloning the development container in a remote pc
try if you can clone it in another folder. 


### GPU not found
You can give the container GPU ability with

    deploy:
      resources:
        reservations:
          devices:
            - capabilities: ["gpu"]


### No realtime kernel

To work the franka panda needs a realtime kernel. Either you already have one installed and need to reboot to choose a kernel in the advanced settings. If you don't have a real time kernel you need to install one [explanation](https://frankaemika.github.io/docs/installation_linux.html#setting-up-the-real-time-kernel)
