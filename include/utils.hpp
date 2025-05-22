#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include <opencv2/opencv.hpp>
#include <vector>

// 1. �������� �����������
cv::Mat load_image(const std::string& filename);
void saveImage(const std::string& path, const cv::Mat& image);

// 2. �������������� � YCbCr
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
std::vector<cv::Mat> applyDCTToBlocks(const std::vector<cv::Mat>& blocks);
//TODO ����������� �������� �������
cv::Mat applyIDCT(const cv::Mat& block);
std::vector<cv::Mat> applyIDCTToBlocks(const std::vector<cv::Mat>& blocks);


// 6. �����������
// ���������� ����������� ������� ����������� ��� ���������� ������ (Y)
cv::Mat getStandardLuminanceQuantTable();
// ���������� ����������� ������� ����������� ��� �������� ������� (Cb, Cr)
cv::Mat getStandardChrominanceQuantTable();
// ����������� ������ ����� � ������� ������� �����������
cv::Mat quantizeBlock(const cv::Mat& block, const cv::Mat& quantTable);
// ����������� ���� ������
std::vector<cv::Mat> quantizeBlocks(const std::vector<cv::Mat>& dctBlocks, const cv::Mat& quantTable);
// ������������� ������ �����
cv::Mat dequantizeBlock(const cv::Mat& block, const cv::Mat& qTable);
// ������������� ������� ������
std::vector<cv::Mat> dequantizeBlocks(const std::vector<cv::Mat>& blocks, const cv::Mat& qTable);


// 7. ��������������� ������������
// ����������� ������� 8x8 � ������ ������ 64 (������-������������)
std::vector<float> zigzagScan(const cv::Mat& block);
// �������� ������-�������������� � �� ������� � ������� 8x8
cv::Mat zigzagUnscan(const std::vector<float>& zigzag);


// 8. RLE
using RLEVector = std::vector<std::pair<int, float>>;
// ����������� RLE: ���� � ������ 64 ��������
RLEVector runLengthEncode(const std::vector<float>& input);
// ������������� RLE: ���� � ���� (����� ������, ��������)
std::vector<float> runLengthDecode(const RLEVector& encoded);


// ������ ��� ������
std::vector<RLEVector> processChannel(const cv::Mat& channel, const cv::Mat& qTable);


#endif
