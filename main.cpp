#include "BundleAdjuster.h"
#include "DataLoader.h"
#include "Detector.h"
#include "Matcher.h"

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

int main() {
    KITTILoader kitti("/run/media/tanmay/PATRIOT/Datasets/KITTI_Odom/dataset/sequences/00");

    Detector feat;
    Matcher matcher;
    BundleAdjuster ba;

    cv::Mat lastImg;
    std::vector<cv::KeyPoint> lastKeypoints;
    cv::Mat lastDescriptors;

    int numFrames = 0;
    while (kitti.hasImages()) {
        auto img = kitti.next();

        // Get keypoints and descriptors
        std::vector<cv::KeyPoint> keypoints;
        cv::Mat descriptors;
        feat.getDetector()->detectAndCompute(img, cv::noArray(), keypoints, descriptors);

        if (numFrames > 0) {
            // Compute matches from the last frame
            auto matchedPoints =
                matcher.match(descriptors, lastDescriptors, keypoints, lastKeypoints);

            std::cout << "Matched " << matchedPoints.size() << " points" << std::endl;
            // Compute the fundamental matrix
            cv::Matx33d fundamental = ba.computeFundamentalMatrix(matchedPoints);

            std::cout << "Fundamental matrix:\n" << fundamental << std::endl;
        }

        // keypoint img
        cv::Mat keypointImg;
        cv::drawKeypoints(img, keypoints, keypointImg);

        // cv::imshow("KITTI sequence", kitti.next());
        cv::imshow("KITTI sequence", keypointImg);
        cv::waitKey(33);

        // Update
        lastImg = img;
        lastKeypoints = keypoints;
        lastDescriptors = descriptors;
        numFrames++;
    }
}