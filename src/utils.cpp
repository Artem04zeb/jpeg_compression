#include "utils.hpp"

cv::Mat convertToYCbCr(const cv::Mat& rgb_image) {
    cv::Mat ycbcr;
    cv::cvtColor(rgb_image, ycbcr, cv::COLOR_BGR2YCrCb);
    return ycbcr;
}

cv::Mat convertToRGB(const cv::Mat& ycbcr_image) {
    cv::Mat rgb;
    cv::cvtColor(ycbcr_image, rgb, cv::COLOR_YCrCb2BGR);
    return rgb;
}
