#pragma once

#include <ceres/ceres.h>
#include <opencv2/core/types.hpp>

#include <vector>

/**
 * Uses bundle adjustment to optimize the R and t matrices as well as the camera parameters
 */
class Optimizer {
public:
    Optimizer() {}
};