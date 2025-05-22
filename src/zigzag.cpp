#pragma once

#include "utils.hpp"

static const int zigzagOrder[64][2] = {
    {0,0},{0,1},{1,0},{2,0},{1,1},{0,2},{0,3},{1,2},
    {2,1},{3,0},{4,0},{3,1},{2,2},{1,3},{0,4},{0,5},
    {1,4},{2,3},{3,2},{4,1},{5,0},{6,0},{5,1},{4,2},
    {3,3},{2,4},{1,5},{0,6},{0,7},{1,6},{2,5},{3,4},
    {4,3},{5,2},{6,1},{7,0},{7,1},{6,2},{5,3},{4,4},
    {3,5},{2,6},{1,7},{2,7},{3,6},{4,5},{5,4},{6,3},
    {7,2},{7,3},{6,4},{5,5},{4,6},{3,7},{4,7},{5,6},
    {6,5},{7,4},{7,5},{6,6},{5,7},{6,7},{7,6},{7,7}
};

std::vector<float> zigzagScan(const cv::Mat& block) {
    std::vector<float> result(64);
    for (int i = 0; i < 64; ++i) {
        int y = zigzagOrder[i][0];
        int x = zigzagOrder[i][1];
        result[i] = block.at<float>(y, x);
    }
    return result;
}

cv::Mat zigzagUnscan(const std::vector<float>& zigzag) {
    cv::Mat block(8, 8, CV_32F, cv::Scalar(0));
    for (int i = 0; i < 64; ++i) {
        int y = zigzagOrder[i][0];
        int x = zigzagOrder[i][1];
        block.at<float>(y, x) = zigzag[i];
    }
    return block;
}
