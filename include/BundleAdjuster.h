#pragma once

#include <ceres/ceres.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/sfm.hpp>

#include <iostream>
#include <vector>

/**
 * Uses bundle adjustment to optimize the R and t matrices as well as the camera parameters
 */
class BundleAdjuster {
public:
    BundleAdjuster() {}

    cv::Matx33d computeFundamentalMatrix(
        const std::vector<std::pair<cv::Point2f, cv::Point2f>>& pointCorrespondences) {
        // Estimate the fundamental matrix using Hartley's 8-point algorithm
        cv::Mat view1(2, pointCorrespondences.size(), CV_64F);
        cv::Mat view2(2, pointCorrespondences.size(), CV_64F);

        for (int i = 0; i < pointCorrespondences.size(); i++) {
            const auto& view1Pt = pointCorrespondences[i].first;
            const auto& view2Pt = pointCorrespondences[i].second;

            view1.at<double>(0, i) = view1Pt.x;
            view1.at<double>(1, i) = view1Pt.y;

            view2.at<double>(0, i) = view2Pt.x;
            view2.at<double>(1, i) = view2Pt.y;
        }

        cv::Matx33d fundamental;
        cv::sfm::normalizedEightPointSolver(view1, view2, fundamental);

        return fundamental;
    }

private:
    struct ReprojectionError {
        ReprojectionError(float observedX, float observedY)
            : _observedX(observedX), _observedY(observedY) {}

        template <typename T>
        bool operator()(const T* const camera, const T* const point, T* residuals) {
            ;
        }

        float _observedX, _observedY;
    };
};