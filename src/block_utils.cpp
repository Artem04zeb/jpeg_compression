#pragma once

#include "utils.hpp"


cv::Mat pad_to_block_size(const cv::Mat& channel, int blockSize = 8) {
    //TODO Реализовать проверку на размеры
    int paddedRows = ((channel.rows + blockSize - 1) / blockSize) * blockSize;
    int paddedCols = ((channel.cols + blockSize - 1) / blockSize) * blockSize;

    cv::Mat padded;
    cv::copyMakeBorder(channel, padded,
        0, paddedRows - channel.rows,
        0, paddedCols - channel.cols,
        cv::BORDER_CONSTANT, 0);
    return padded;
}

std::vector<cv::Mat> split_into_blocks(const cv::Mat& channel, int blockSize) {
    std::vector<cv::Mat> blocks;

    for (int y = 0; y < channel.rows; y += blockSize) {
        for (int x = 0; x < channel.cols; x += blockSize) {
            cv::Rect roi(x, y, blockSize, blockSize);
            blocks.push_back(channel(roi).clone());
        }
    }

    return blocks;
}

cv::Mat merge_blocks(const std::vector<cv::Mat>& blocks, int width, int height, int blockSize) {
    int rows = ((height + blockSize - 1) / blockSize) * blockSize;
    int cols = ((width + blockSize - 1) / blockSize) * blockSize;
    cv::Mat full(rows, cols, blocks[0].type(), cv::Scalar(0));

    int blockIndex = 0;
    for (int y = 0; y < rows; y += blockSize) {
        for (int x = 0; x < cols; x += blockSize) {
            if (blockIndex >= blocks.size()) break;
            blocks[blockIndex++].copyTo(full(cv::Rect(x, y, blockSize, blockSize)));
        }
    }
    return full(cv::Rect(0, 0, width, height)).clone();
}

void centerBlocks(std::vector<cv::Mat>& blocks) {
    for (auto& block : blocks) {
        block = block - 128;
    }
}

void decenterBlocks(std::vector<cv::Mat>& blocks) {
    for (auto& block : blocks) {
        block = block + 128;
    }
}