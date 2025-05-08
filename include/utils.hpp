#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include <opencv2/opencv.hpp>

cv::Mat convertToYCbCr(const cv::Mat& rgb_image);
cv::Mat convertToRGB(const cv::Mat& ycbcr_image);  // на будущее

#endif // COLOR_UTILS_HPP
