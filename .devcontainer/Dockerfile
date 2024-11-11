FROM chillerrobot/ros-noetic-moveit-panda:first

#RUN apt-get install -y --no-install-recommends *add your installs here*
#RUN pip3 install *add your packages here*

RUN apt-get update && apt-get install -y ros-noetic-panda-moveit-config
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && roscd panda_moveit_config"
RUN apt-get install -y ros-noetic-rviz-visual-tools
RUN apt-get update

# Install Mesa libraries (for AMD/ATI GPUs)
RUN apt-get update && \
    apt-get -y install libgl1-mesa-glx libgl1-mesa-dri && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /home/coder/catkin_ws
RUN mkdir -p src
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && catkin_make"
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && source devel/setup.bash"

RUN echo "source /home/coder/catkin_ws/devel/setup.bash" >> ~/.bashrc