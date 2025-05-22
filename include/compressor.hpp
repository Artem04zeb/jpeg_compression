#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "utils.hpp"

// ��� �������� ������ ������
struct CompressedChannel {
    std::vector<RLEVector> blocks;
    int width;
    int height;
};

// �� ������ �����������
struct CompressedImage {
    CompressedChannel Y;
    CompressedChannel Cb;
    CompressedChannel Cr;
};

// ���������� � ����
void saveCompressed(const std::string& filename,
    const std::vector<RLEVector>& Y,
    const std::vector<RLEVector>& Cb,
    const std::vector<RLEVector>& Cr,
    int width,
    int height);

// �������� �� �����
CompressedImage loadCompressed(const std::string& filename);
