#include "utils.hpp"

cv::Mat loadImage(const std::string& filename) {
    //TODO Реализовать проверку
    return cv::imread(filename);
}

cv::Mat convertToYCbCr(const cv::Mat& rgb_image) {
    // Как выполняется трансформирование
    // https://docs.opencv.org/3.4/de/d25/imgproc_color_conversions.html#color_convert_rgb_ycrcb
    cv::Mat ycbcr;
    cv::cvtColor(rgb_image, ycbcr, cv::COLOR_BGR2YCrCb);
    return ycbcr;
}

cv::Mat convertToRGB(const cv::Mat& ycbcr_image) {
    cv::Mat rgb;
    cv::cvtColor(ycbcr_image, rgb, cv::COLOR_YCrCb2BGR);
    return rgb;
}
