# Build the Docker container using the specified Dockerfile
docker build -f "$(Join-Path $PSScriptRoot '.devcontainer/Dockerfile')" -t container-ros-noetic-moveit-panda .