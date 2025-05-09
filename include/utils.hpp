#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include <opencv2/opencv.hpp>

// 1. �������� �����������
cv::Mat load_image(const std::string& filename);


// 2. 
// �������������� � YCbCr
cv::Mat convert_to_YCbCr(const cv::Mat& rgb_image);
cv::Mat convert_to_BGR(const cv::Mat& ycbcr_image);  // �� �������


// 3. ������� ������� �� �����
// ���������� ����������� �������� �����������, ����� ��� ���� ������ blockSize
cv::Mat pad_to_block_size(const cv::Mat& channel, int blockSize);

// ������� ����������� �� ����� 
std::vector<cv::Mat> split_into_blocks(const cv::Mat& channel, int blockSize);

// ����������� ������ � ���� �����������
cv::Mat merge_blocks(const std::vector<cv::Mat>& blocks, int width, int height, int blockSize);


// 4. ������������� ��������
void centerBlocks(std::vector<cv::Mat>& blocks);
void decenterBlocks(std::vector<cv::Mat>& blocks);

// 5.
// ��������� ���������� ���������� �������������� (DCT) � ����� 8x8
cv::Mat applyDCT(const cv::Mat& block);

// �������� ��������������
std::vector<cv::Mat> applyDCTToBlocks(const std::vector<cv::Mat>& blocks);

/*
// 5. DCT
cv::Mat applyDCT(const cv::Mat& block);
std::vector<cv::Mat> applyDCTToBlocks(const std::vector<cv::Mat>& blocks);
cv::Mat applyIDCT(const cv::Mat& block);
std::vector<cv::Mat> applyIDCTToBlocks(const std::vector<cv::Mat>& blocks);

// 6. �����������
cv::Mat quantizeBlock(const cv::Mat& dctBlock, const QuantTable& qtable);
std::vector<cv::Mat> quantizeBlocks(const std::vector<cv::Mat>& dctBlocks, const QuantTable& qtable);
cv::Mat dequantizeBlock(const cv::Mat& qBlock, const QuantTable& qtable);
std::vector<cv::Mat> dequantizeBlocks(const std::vector<cv::Mat>& qBlocks, const QuantTable& qtable);

// 7. ��������������� ������������
ZigZagVector zigzagScan(const cv::Mat& block);
cv::Mat zigzagUnscan(const ZigZagVector& vec);

// 8. RLE
RLEVector runLengthEncode(const ZigZagVector& vec);
ZigZagVector runLengthDecode(const RLEVector& rle);

// 9. ���������� � �������� ������� �����������
void saveCompressed(const std::string& filename,
    const std::vector<RLEVector>& y,
    const std::vector<RLEVector>& cb,
    const std::vector<RLEVector>& cr);
CompressedImage loadCompressed(const std::string& filename);

// ��������������� ������� (�� �������)
QuantTable getStandardLuminanceQuantTable();
QuantTable getStandardChrominanceQuantTable();
*/



/*
#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

// ����
using ZigZagVector = std::vector<int>;
using RLEPair = std::pair<int, int>;
using RLEVector = std::vector<RLEPair>;
using QuantTable = cv::Mat;

struct CompressedChannel {
    std::vector<RLEVector> blocks;
    int width;
    int height;
};

struct CompressedImage {
    CompressedChannel Y;
    CompressedChannel Cb;
    CompressedChannel Cr;
};
*/
#endif 