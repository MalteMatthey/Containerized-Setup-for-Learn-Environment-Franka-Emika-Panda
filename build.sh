#!/bin/sh
cd "$(dirname "$0")/.devcontainer"
sudo docker build -t container-ros-noetic-moveit-panda .