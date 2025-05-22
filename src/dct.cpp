#pragma once

#include "utils.hpp"

cv::Mat applyDCT(const cv::Mat& block) {
    //TODO ����������� �������  
    // ���� ���������, ��� ���������� ������� ������ 8�8
    CV_Assert(block.rows == 8 && block.cols == 8);
    CV_Assert(block.type() == CV_32F);

    cv::Mat dctBlock;
    cv::dct(block, dctBlock); // ������ DCT-��������������
    return dctBlock;
}

std::vector<cv::Mat> applyDCTToBlocks(const std::vector<cv::Mat>& blocks) {
    std::vector<cv::Mat> dctBlocks;

    dctBlocks.reserve(blocks.size());

    for (const auto& block : blocks) {
        CV_Assert(block.rows == 8 && block.cols == 8);
        CV_Assert(block.type() == CV_32F);
        dctBlocks.push_back(applyDCT(block));
    }

    return dctBlocks;
}

cv::Mat applyIDCT(const cv::Mat& block) {
    cv::Mat idctBlock;
    cv::idct(block, idctBlock);
    return idctBlock;
}

std::vector<cv::Mat> applyIDCTToBlocks(const std::vector<cv::Mat>& blocks) {
    std::vector<cv::Mat> result;
    for (const auto& block : blocks) {
        //result.push_back(applyIDCT(blocks));

        //� ��� ������
        cv::Mat idctBlock;
        cv::idct(block, idctBlock);
        result.push_back(idctBlock);
    }
    return result;
}