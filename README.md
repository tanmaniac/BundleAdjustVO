# Visual Odometry Through Bundle Adjustment

A small side project to explore geometric computer vision and photogrammetry (and maybe even ORB SLAM?).

## Setup

Arch Linux:

```bash
sudo pacman -Sy boost eigen google-glog gflags
yay ceres-solver
yay --editmenu opencv-cuda

mkdir build
cd build
cmake ..
make -j$(nproc)
```

In the opencv-cuda build, modify the PKGBUILD to use `gcc` for its CUDA compiler and change `make` to `make -j$(nproc)`.