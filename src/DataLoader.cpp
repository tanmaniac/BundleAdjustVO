#include "../include/DataLoader.h"

#include <boost/filesystem.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

namespace fs = boost::filesystem;

KITTILoader::KITTILoader(const std::string& sequence) : _curImg(0) {
    // Find all the left-camera images in the sequence and add their paths to the vector of paths
    fs::path sequencePath(sequence);

    if (fs::exists(sequencePath) && fs::is_directory(sequencePath)) {
        auto leftImages = sequencePath / "image_2";
        if (fs::exists(leftImages) && fs::is_directory(leftImages)) {
            for (const auto& x : fs::directory_iterator(leftImages)) {
                _images.push_back(x.path().string());
            }

            std::sort(_images.begin(), _images.end());
        }
    } else {
        std::cerr << "No such path " << sequencePath << " exists!" << std::endl;
    }
}

bool KITTILoader::hasImages() { return _curImg < _images.size(); }

cv::Mat KITTILoader::next() {
    if (!hasImages()) {
        throw std::runtime_error("No more images in the sequence!");
    }

    return cv::imread(_images[_curImg++]);
}