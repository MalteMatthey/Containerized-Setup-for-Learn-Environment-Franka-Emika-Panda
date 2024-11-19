#!/bin/sh
cd "$(dirname "$0")"
sudo docker build -f .devcontainer/Dockerfile -t container-ros-noetic-moveit-panda .