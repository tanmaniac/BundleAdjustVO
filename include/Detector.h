#pragma once

#include <opencv2/features2d.hpp>

/**
 * Uses SURF to extract features and feature descriptors from input images
 */
class Detector {
public:
    Detector(int nfeatures = 500,
             float scaleFactor = 1.2f,
             int nlevels = 8,
             int edgeThreshold = 31,
             int firstLevel = 0,
             int WTA_K = 2,
             cv::ORB::ScoreType scoreType = cv::ORB::HARRIS_SCORE,
             int patchSize = 31,
             int fastThreshold = 20)
        : _detector(cv::ORB::create(nfeatures,
                                    scaleFactor,
                                    nlevels,
                                    edgeThreshold,
                                    firstLevel,
                                    WTA_K,
                                    scoreType,
                                    patchSize,
                                    fastThreshold)) {}

    cv::Ptr<cv::ORB> getDetector() { return _detector; }

private:
    cv::Ptr<cv::ORB> _detector;
};