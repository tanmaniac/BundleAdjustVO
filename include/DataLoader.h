#pragma once

#include <Eigen/Dense>
#include <opencv2/core/core.hpp>

#include <string>
#include <vector>

class KITTILoader {
public:
    KITTILoader(const std::string& sequence);

    bool hasImages();

    cv::Mat next();

private:
    int _curImg;
    std::vector<std::string> _images;
    Eigen::Projective3f _projection;
};
