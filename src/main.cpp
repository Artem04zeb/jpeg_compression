#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main() {
    
    cv::Mat img = cv::imread("D:\\Desktop\\курсовая работа\\data\\input.jpg");
    //cv::Mat ycbcr = convertToYCbCr(img);
    cv::imshow("YCbCr", img);
    cv::waitKey(0);
}
