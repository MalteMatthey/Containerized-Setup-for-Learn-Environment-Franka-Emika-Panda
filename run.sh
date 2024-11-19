#!/bin/sh

# WITHOUT HARDWARE ACCELERATION
# cd "$(dirname "$0")/.devcontainer"
# docker run -it --env-file .env --env="DISPLAY=$DISPLAY" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" container-ros-noetic-moveit-panda /bin/bash

# WITH HARDWARE ACCELERATION
cd "$(dirname "$0")/.devcontainer"
xhost +
if lspci | grep -i nvidia > /dev/null; then
    docker run -it \
        --gpus all \
        --env-file .env \
        --env="DISPLAY=$DISPLAY" \
        --volume="/tmp/.X11-unix:/tmp/.X11-unix" \
        container-ros-noetic-moveit-panda /bin/bash
else
    docker run -it \
        --device=/dev/dri \
        --group-add video \
        --env-file .env \
        --env="DISPLAY=$DISPLAY" \
        --volume="/tmp/.X11-unix:/tmp/.X11-unix" \
        container-ros-noetic-moveit-panda /bin/bash
fi