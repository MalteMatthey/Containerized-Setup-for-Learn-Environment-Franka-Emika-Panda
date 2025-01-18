# ROS Noetic Standard Container with Preinstalled Learn Environment Plugin

> **⚠️ WARNING:** This README is for setting up the container with all functionalities. For the Learn Environment Plugin, follow the instructions in this README first. After the installation, refer to [GETTING_STARTED.md](./catkin_ws/src/learn_environment/tasks/GETTING_STARTED.md) for starting the tutorial or [CONTRIBUTE.md](./catkin_ws/src/learn_environment/developer_docs/CONTRIBUTE.md) for contribution guidelines (creating new tasks & extending the plugin) in the [plugin's repository](https://gitlab.kit.edu/kit/aifb/BIS/lehre/seminare/programmieren_3/202425/gruppe-3/learn-environment-franka-emika-panda). 

This repository provides a Visual Studio Code development container with ROS Noetic installed to control a Franka Panda Robot in both simulation and real environments. It also has the Learn Environment plugin for RViz preinstalled and is optimised so you can start learning how to work with the robot immediatly.


## Features

- ROS Noetic
- Support for Franka Panda
- Precompiled MoveIt
- Preinstalled Learn Environment plugin for RViz

## Installation

When to Use Devcontainers:

**Benefits of Devcontainers:**
- Easier setup
- No worries about connecting the display due to Web Desktop Environment

**Benefits of Not Using Devcontainers:**
- Still very easy setup
- Less overhead
- Faster build
- Display forwarding already implemented
- Easier to enable GPU support on non-NVIDIA graphic cards
- Native application windows without the need for NoVNC or other web-based desktop virtualization.

### Local Windows Installation

<details>
<summary>Using Devcontainer</summary>

1. Install [Visual Studio Code](https://code.visualstudio.com/)
    - Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension (ID: ms-vscode-remote.remote-containers)
2. Install [WSL2](https://learn.microsoft.com/en-us/windows/wsl/install)
3. Install [Docker](https://docs.docker.com/desktop/install/windows-install/)
    - You may need to install [docker-compose](https://docs.docker.com/compose/) with `pip install docker-compose`
4. Create an SSH key in your WSL environment and add it to your git.ssc.kit.edu SSH keys. [Explanation](https://docs.gitlab.kit.edu/en/getting_started/#1-ssh-connection-using-ssh-keys)
5. Clone the repository in your WSL environment:
    ```bash
    git clone --recurse-submodules git@gitlab.kit.edu:kit/aifb/BIS/lehre/seminare/programmieren_3/202425/gruppe-3/containerized-setup-learn-environment-franka-emika-panda.git
    ```
6. Open the repository folder in VS Code.
7. Open the container in a Docker environment:
    ```bash
    ctrl + shift + p
    ```
    Select `Dev-Containers: Open in Container`. All necessary tools will be installed.

</details>

<details>
<summary>Without Devcontainer</summary>

1. Install [Visual Studio Code](https://code.visualstudio.com/)
    - Install the [Docker extension](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker) (ID: ms-azuretools.vscode-docker)
    - Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension (ID: ms-vscode-remote.remote-containers)
2. Install [WSL2](https://learn.microsoft.com/en-us/windows/wsl/install)
3. Install [Docker](https://docs.docker.com/desktop/install/windows-install/)
    - You may need to install [docker-compose](https://docs.docker.com/compose/) with `pip install docker-compose`
4. Create an SSH key in your WSL environment and add it to your git.ssc.kit.edu SSH keys. [Explanation](https://docs.gitlab.kit.edu/en/getting_started/#1-ssh-connection-using-ssh-keys)
5. Clone the repository in your WSL environment:
    ```bash
    git clone --recurse-submodules git@gitlab.kit.edu:kit/aifb/BIS/lehre/seminare/programmieren_3/202425/gruppe-3/containerized-setup-learn-environment-franka-emika-panda.git
    ```
6. Open the repository folder in VS Code.
7. Build the container:
    ```bash
    ./build.ps1
    ```
8. Start the container:
    ```bash
    ./run.ps1
    ```
9. Attach VS Code to the container:
    - Click on the Docker extension (left sidebar in VS Code).
    - Find the running container, right-click on it, and select `Attach VS Code`. This will open a new VS Code window inside the container.
10. Make the display available for the container:
    - Install [VcXsrv](https://sourceforge.net/projects/vcxsrv/). 
    - Start the `XLaunch` Application (e.g. from Windows Start Menu)
    - Select `Multiple windows` and set `Display number` to `0`. Click `next`.
    - Select `Start no client`. Click `next`.
    - Also check the `Disable accesss control` box. Click `next` and `finish`.

</details>

### Local Linux Installation

<details>
<summary>Using Devcontainer</summary>

1. Install [Visual Studio Code](https://code.visualstudio.com/)
    - Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension (ID: ms-vscode-remote.remote-containers)
2. Install [Docker](https://docs.docker.com/engine/install/ubuntu/)
3. Create an SSH key in your WSL environment and add it to your git.ssc.kit.edu SSH keys. [Explanation](https://docs.gitlab.kit.edu/en/getting_started/#1-ssh-connection-using-ssh-keys)
4. Clone the repository in your environment:
    ```bash
    git clone --recurse-submodules git@gitlab.kit.edu:kit/aifb/BIS/lehre/seminare/programmieren_3/202425/gruppe-3/containerized-setup-learn-environment-franka-emika-panda.git
    ```
5. Open the repository folder in VS Code.
6. Open the container in a Docker environment:
    ```bash
    ctrl + shift + p
    ```
    Select `Dev-Containers: Open in Container`. All necessary tools will be installed.

</details>

<details>
<summary>Without Devcontainer</summary>

1. Install [Visual Studio Code](https://code.visualstudio.com/)
    - Install the [Docker extension](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker) (ID: ms-azuretools.vscode-docker)
    - Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension (ID: ms-vscode-remote.remote-containers)
2. Install [Docker](https://docs.docker.com/engine/install/ubuntu/)
    - You may need to install [docker-compose](https://docs.docker.com/compose/) with `pip install docker-compose`
3. Create an SSH key in your WSL environment and add it to your git.ssc.kit.edu SSH keys. [Explanation](https://docs.gitlab.kit.edu/en/getting_started/#1-ssh-connection-using-ssh-keys)
4. Clone the repository in your environment:
    ```bash
    git clone --recurse-submodules git@gitlab.kit.edu:kit/aifb/BIS/lehre/seminare/programmieren_3/202425/gruppe-3/containerized-setup-learn-environment-franka-emika-panda.git
    ```
5. Open the repository folder in VS Code.
6. Build the container:
    ```bash
    ./build.sh
    ```
7. Start the container:
    ```bash
    ./run.sh
    ```
8. Attach VS Code to the container:
    - Click on the Docker extension (left sidebar in VS Code).
    - Find the running container, right-click on it, and select `Attach VS Code`. This will open a new VS Code window inside the container.

</details>

## Functions

### Desktop Environment (Devcontainer setup only)

Access the desktop environment of the container in your browser at [http://localhost:6080/](http://localhost:6080/). All windows you open in the container will be shown here.

### Start the Learn Environment tutorial 

To get started with the plugin, follow the instructions provided [here](./catkin_ws/src/learn_environment/tasks/GETTING_STARTED.md). If VS Code does not automatically open the `/catkin_ws/src/learn_environment/tasks` folder, please navigate to it manually. This is the starting point of the tutorial.

![Learn Environment](/screenshots/plugin.png)

### Control the Real Panda

Activate the Panda FCI in the DESK environment with "Activate FCI". The robot LEDs should turn blue.

#### MoveIt Position Controller

To control the Panda with MoveIt, execute:
```bash
roslaunch panda_moveit_config franka_control.launch robot_ip:=172.16.0.2
```
You can use RVIZ and MoveIt to send the robot to coordinates in the desktop environment.

If the robot gets stuck or you move it by hand, recover it with:
```bash
rostopic pub -1 /franka_control/error_recovery/goal franka_msgs/ErrorRecoveryActionGoal "{}"
```

#### Cartesian Impedance Controller

To control the Panda with a Cartesian impedance controller, execute:
```bash
roslaunch franka_example_controllers cartesian_impedance_example_controller.launch robot_ip:=172.16.0.2
```
You can move the robot in RVIZ in the desktop environment.

### Panda Gazebo (Simulation)

#### Cartesian Impedance Controller

To simulate the Panda with a Cartesian impedance controller, execute:
```bash
roslaunch franka_gazebo panda.launch x:=-0.5 \
world:=$(rospack find franka_gazebo)/world/stone.sdf \
controller:=cartesian_impedance_example_controller \
rviz:=true
```
This opens RVIZ and Gazebo with a simulation of the Panda robot.

![Gazebo RVIZ Sim](/screenshots/gazebocartesianrvizsim.png)

#### MoveIt Position Controller

To simulate the Panda with a MoveIt position controller, execute:
```bash
roslaunch panda_moveit_config demo_gazebo.launch rviz_tutorial:=true
```
This opens RVIZ and Gazebo with a simulation of the Panda robot. You can add a motion planner in RVIZ if needed.

### Create Your Own Package/Node

To create your own ROS package, create a catkin package in `/workspace/catkin_ws/src`. You can also clone another ROS package and work with it. [Create a ROS Package](http://wiki.ros.org/ROS/Tutorials/CreatingPackage)

Compile the workspace with `catkin_make` in `/workspace/catkin_ws`. To use the compiled functions, source the workspace setup.bash with:
```bash
source /workspace/catkin_ws/devel/setup.bash
```

## Error Handling

### Problems Cloning the Development Container on a Remote PC

Try cloning the repository in another folder.

### Container Doesn't Start on Linux (MIT-Magic Cookie)

Activating CPU virtualization might help.

### GPU Not Found

Enable GPU support for the container with:
```yaml
deploy:
  resources:
    reservations:
      devices:
        - capabilities: ["gpu"]
```

Just uncomment these lines in `docker-compose.yml`.

### No Realtime Kernel

The Franka Panda requires a realtime kernel. If you don't have one, install it following [this explanation](https://frankaemika.github.io/docs/installation_linux.html#setting-up-the-real-time-kernel). Reboot and choose the realtime kernel in the advanced settings.
