#pragma once

#include "utils.hpp"

cv::Mat load_image(const std::string& filename) {
    //TODO Реализовать проверку
    // https://docs.opencv.org/3.4/dc/da3/tutorial_copyMakeBorder.html
    // good example how to operate over unsuccessfull read
    return cv::imread(filename);
}

void saveImage(const std::string& path, const cv::Mat& image) {
    cv::imwrite(path, image);
}

// Работа над функциями
std::vector<RLEVector> processChannel(const cv::Mat& channel, const cv::Mat& qTable) {
    std::cout << "[INFO processChannel] Original size: " << channel.size() << std::endl;
    
    // Чтобы применять DCT, изображение разбивается на блоки 8×8. Это дополняет изображение до нужного размера
    cv::Mat padded = pad_to_block_size(channel, 8);
    std::cout << "[INFO processChannel] After pad: " << padded.size() << std::endl;

    // Разбиение на блоки
    std::vector<cv::Mat> blocks = split_into_blocks(padded, 8);
    std::cout << "[INFO processChannel] Amount of blocks: " << blocks.size() << std::endl;

    // Центрирование значений
    centerBlocks(blocks);
    std::cout << "[INFO processChannel] Centration of blocks completed" << std::endl;

    // Применение DCT
    std::vector<cv::Mat> dctBlocks = applyDCTToBlocks(blocks);
    std::cout << "[INFO processChannel] DCT Application of blocks completed" << std::endl;

    // Квантование
    std::vector<cv::Mat> qBlocks = quantizeBlocks(dctBlocks, qTable);
    std::cout << "[INFO processChannel] Quantation completed" << std::endl;

    // Зигзагообразное сканирование + RLE
    std::vector<RLEVector> encoded;
    for (const auto& block : qBlocks) {
        auto zz = zigzagScan(block);
        encoded.push_back(runLengthEncode(zz));
    }
    std::cout << "[INFO processChannel] ZZ and RLE completed" << std::endl;

    return encoded;
}