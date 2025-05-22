#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "utils.hpp"

// Для хранения одного канала
struct CompressedChannel {
    std::vector<RLEVector> blocks;
    int width;
    int height;
};

// Всё сжатое изображение
struct CompressedImage {
    CompressedChannel Y;
    CompressedChannel Cb;
    CompressedChannel Cr;
};

// Сохранение в файл
void saveCompressed(const std::string& filename,
    const std::vector<RLEVector>& Y,
    const std::vector<RLEVector>& Cb,
    const std::vector<RLEVector>& Cr,
    int width,
    int height);

// Загрузка из файла
CompressedImage loadCompressed(const std::string& filename);
