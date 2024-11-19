FROM chillerrobot/ros-noetic-moveit-panda:first

RUN apt-get update && apt-get install -y ros-noetic-panda-moveit-config
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && roscd panda_moveit_config"
RUN apt-get install -y ros-noetic-rviz-visual-tools
RUN apt-get update

# Install Mesa libraries (for AMD/ATI GPUs)
RUN apt-get update && \
    apt-get -y install libgl1-mesa-glx libgl1-mesa-dri && \
    rm -rf /var/lib/apt/lists/*

# Install Qt5
RUN apt-get update && apt-get install -y qt5-default

# Install nano
RUN apt-get update && apt-get install -y nano

# Install nlohmann/json
RUN apt-get update && apt-get install -y nlohmann-json3-dev

WORKDIR /catkin_ws
RUN mkdir -p src

# Copy the entire catkin_ws folder into the container
COPY catkin_ws /catkin_ws

# Build the workspace
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && catkin_make"

# Source the setup.bash file
RUN echo "source /catkin_ws/devel/setup.bash" >> ~/.bashrc