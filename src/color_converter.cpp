#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include "utils.hpp"

cv::Mat convert_to_YCbCr(const cv::Mat& rgb_image) {
    cv::Mat ycbcr;
    cv::cvtColor(rgb_image, ycbcr, cv::COLOR_BGR2YCrCb);
    return ycbcr;
}

cv::Mat convert_to_BGR(const cv::Mat& ycbcr_image) {
    cv::Mat rgb;
    cv::cvtColor(ycbcr_image, rgb, cv::COLOR_YCrCb2BGR);
    return rgb;
}