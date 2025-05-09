#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include <opencv2/opencv.hpp>

cv::Mat convertToYCbCr(const cv::Mat& rgb_image);
cv::Mat convertToRGB(const cv::Mat& ycbcr_image);  // на будущее

#endif // COLOR_UTILS_HPP
///
/*
#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

// Типы
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

// 1. Загрузка изображения
cv::Mat loadImage(const std::string& filename);

// 2. Преобразование BGR -> YCbCr
void convertBGRToYCbCr(const cv::Mat& bgr, cv::Mat& y, cv::Mat& cb, cv::Mat& cr);
void convertYCbCrToBGR(const cv::Mat& y, const cv::Mat& cb, const cv::Mat& cr, cv::Mat& bgr);

// 3. Деление на блоки
cv::Mat padToBlockSize(const cv::Mat& channel, int blockSize = 8);
std::vector<cv::Mat> splitIntoBlocks(const cv::Mat& channel, int blockSize = 8);
cv::Mat mergeBlocks(const std::vector<cv::Mat>& blocks, int width, int height);

// 4. Центрирование значений
void centerBlock(cv::Mat& block);
void centerBlocks(std::vector<cv::Mat>& blocks);
void decenterBlock(cv::Mat& block);
void decenterBlocks(std::vector<cv::Mat>& blocks);

// 5. DCT
cv::Mat applyDCT(const cv::Mat& block);
std::vector<cv::Mat> applyDCTToBlocks(const std::vector<cv::Mat>& blocks);
cv::Mat applyIDCT(const cv::Mat& block);
std::vector<cv::Mat> applyIDCTToBlocks(const std::vector<cv::Mat>& blocks);

// 6. Квантование
cv::Mat quantizeBlock(const cv::Mat& dctBlock, const QuantTable& qtable);
std::vector<cv::Mat> quantizeBlocks(const std::vector<cv::Mat>& dctBlocks, const QuantTable& qtable);
cv::Mat dequantizeBlock(const cv::Mat& qBlock, const QuantTable& qtable);
std::vector<cv::Mat> dequantizeBlocks(const std::vector<cv::Mat>& qBlocks, const QuantTable& qtable);

// 7. Зигзагообразное сканирование
ZigZagVector zigzagScan(const cv::Mat& block);
cv::Mat zigzagUnscan(const ZigZagVector& vec);

// 8. RLE
RLEVector runLengthEncode(const ZigZagVector& vec);
ZigZagVector runLengthDecode(const RLEVector& rle);

// 9. Сохранение и загрузка сжатого изображения
void saveCompressed(const std::string& filename,
                    const std::vector<RLEVector>& y,
                    const std::vector<RLEVector>& cb,
                    const std::vector<RLEVector>& cr);
CompressedImage loadCompressed(const std::string& filename);

// Вспомогательные функции (по желанию)
QuantTable getStandardLuminanceQuantTable();
QuantTable getStandardChrominanceQuantTable();

*/
