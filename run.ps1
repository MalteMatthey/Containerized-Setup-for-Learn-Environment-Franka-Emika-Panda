# Set the DISPLAY environment variable to the host's address
$env:DISPLAY="host.docker.internal:0.0"

# Check if NVIDIA GPU is present
if (Get-WmiObject Win32_VideoController | Where-Object { $_.Name -like "*NVIDIA*" }) {
    docker run -it `
        --gpus all `
        --env="DISPLAY=$env:DISPLAY" `
        --volume="/tmp/.X11-unix:/tmp/.X11-unix" `
        container-ros-noetic-moveit-panda /bin/bash
} else {
    docker run -it `
        --device=/dev/dri `
        --group-add video `
        --env="DISPLAY=$env:DISPLAY" `
        --volume="/tmp/.X11-unix:/tmp/.X11-unix" `
        container-ros-noetic-moveit-panda /bin/bash
}