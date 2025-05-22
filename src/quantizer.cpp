#pragma once

#include "utils.hpp"

cv::Mat quantizeBlock(const cv::Mat& block, const cv::Mat& quantTable) {
    //TODO Описать проверки
    //CV_Assert(block.rows == 8 && block.cols == 8);
    //CV_Assert(block.type() == CV_32F);
    //CV_Assert(quantTable.rows == 8 && quantTable.cols == 8);
    //CV_Assert(quantTable.type() == CV_32F);

    // Создание изображения
    cv::Mat quantized(8, 8, CV_32F);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            float val = block.at<float>(i, j);
            float q = quantTable.at<float>(i, j);
            quantized.at<float>(i, j) = std::round(val / q);
        }
    }

    return quantized;
}

cv::Mat dequantizeBlock(const cv::Mat& block, const cv::Mat& qTable) {
    cv::Mat result;
    cv::multiply(block, qTable, result);
    return result;
}

std::vector<cv::Mat> quantizeBlocks(const std::vector<cv::Mat>& dctBlocks, const cv::Mat& quantTable) {
    std::vector<cv::Mat> quantizedBlocks;
    quantizedBlocks.reserve(dctBlocks.size());

    for (const auto& block : dctBlocks) {
        quantizedBlocks.push_back(quantizeBlock(block, quantTable));
    }

    return quantizedBlocks;
}

std::vector<cv::Mat> dequantizeBlocks(const std::vector<cv::Mat>& blocks, const cv::Mat& qTable) {
    std::vector<cv::Mat> result;
    for (const auto& block : blocks) {
        result.push_back(dequantizeBlock(block, qTable));
    }
    return result;
}

cv::Mat getStandardLuminanceQuantTable() {
    static const float data[8][8] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68,109,103, 77},
        {24, 35, 55, 64, 81,104,113, 92},
        {49, 64, 78, 87,103,121,120,101},
        {72, 92, 95, 98,112,100,103, 99}
    };
    return cv::Mat(8, 8, CV_32F, (void*)data).clone();
}

cv::Mat getStandardChrominanceQuantTable() {
    static const float data[8][8] = {
        {17, 18, 24, 47, 99, 99, 99, 99},
        {18, 21, 26, 66, 99, 99, 99, 99},
        {24, 26, 56, 99, 99, 99, 99, 99},
        {47, 66, 99, 99, 99, 99, 99, 99},
        {99, 99, 99, 99, 99, 99, 99, 99},
        {99, 99, 99, 99, 99, 99, 99, 99},
        {99, 99, 99, 99, 99, 99, 99, 99},
        {99, 99, 99, 99, 99, 99, 99, 99}
    };
    return cv::Mat(8, 8, CV_32F, (void*)data).clone();
}
