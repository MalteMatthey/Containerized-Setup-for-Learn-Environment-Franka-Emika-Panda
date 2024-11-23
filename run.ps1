# Navigate to the .devcontainer directory
cd "$(Join-Path $PSScriptRoot '.devcontainer')"

# Set the DISPLAY environment variable to the host's address
$env:DISPLAY="host.docker.internal:0.0"

# Check if NVIDIA GPU is present
if (Get-WmiObject Win32_VideoController | Where-Object { $_.Name -like "*NVIDIA*" }) {
    # docker run -it `
    #     --gpus all `
    #     --env-file .env \
    #     --env="DISPLAY=$env:DISPLAY" `
    #     container-ros-noetic-moveit-panda /bin/bash
    echo "DISPLAY1=$env:DISPLAY"

} else {
    docker run -it ` --env="DISPLAY=$env:DISPLAY" ` --env-file .env container-ros-noetic-moveit-panda /bin/bash
    echo "DISPLAY=$env:DISPLAY"
}