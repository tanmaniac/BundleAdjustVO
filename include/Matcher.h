#pragma once

#include <opencv2/features2d.hpp>

class Matcher {
public:
    Matcher(int normType = cv::NormTypes::NORM_L2, bool crossCheck = false)
        : _matcher(cv::BFMatcher::create(normType, crossCheck)) {}

    cv::Ptr<cv::BFMatcher> getMatcher() { return _matcher; }

    // TODO: minimum distance threshold to prevent optimizing over very small points? idk if this is
    // useful @tanmay
    std::vector<std::pair<cv::Point2f, cv::Point2f>>
        match(const cv::Mat& queryDescriptors,
              const cv::Mat& trainDescriptors,
              const std::vector<cv::KeyPoint>& queryPoints,
              const std::vector<cv::KeyPoint>& trainPoints) {
        std::vector<cv::DMatch> matches;

        // Compute matches
        _matcher->match(queryDescriptors, trainDescriptors, matches);

        // Fetch the points from the keypoint matrices
        std::vector<std::pair<cv::Point2f, cv::Point2f>> matchedPoints;
        for (const auto& match : matches) {
            matchedPoints.push_back(
                {queryPoints[match.queryIdx].pt, trainPoints[match.trainIdx].pt});
        }

        return matchedPoints;
    }

private:
    cv::Ptr<cv::BFMatcher> _matcher;
};