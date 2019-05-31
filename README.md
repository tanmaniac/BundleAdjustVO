# Visual Odometry Through Bundle Adjustment

A small side project to explore geometric computer vision and photogrammetry (and maybe even ORB SLAM?).

## Setup

Arch Linux:

```bash
sudo pacman -Sy boost eigen
yay opencv-cuda ceres-solver

mkdir build
cd build
cmake ..
make -j$(nproc)
```