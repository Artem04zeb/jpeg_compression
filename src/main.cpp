#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "compressor.hpp"
#include "utils.hpp"

int main() {
    std::string inputPath = "D:\\Desktop\\курсовая работа\\data\\input3.png";
    std::string compressedPath = "D:\\Desktop\\курсовая работа\\data\\bin-input3.bin";
    std::string restoredPath = "D:\\Desktop\\курсовая работа\\data\\restored-input3.png";

    //// 1. Загрузка изображения
    cv::Mat image = load_image(inputPath);
    if (image.empty()) {
        std::cerr << "Error: failed to load image!" << std::endl;
        return 1;
    }
    std::cout << ">>>>> Image loaded" << std::endl;
    //cv::imshow("TEST Original", image);


    //// 2. Преобразование в YCbCr
    cv::Mat ycbcr = convert_to_YCbCr(image);
    std::cout << ">>>>> Transform to YCbCr completed" << std::endl;

    // Проверка работы конвертера
    // Проверка работы обратного конвертера
    //cv::imshow("TEST convert_to_YCbCr", ycbcr);
    //cv::Mat restored_bgr = convert_to_BGR(ycbcr);
    //cv::imshow("TEST convert_to_BGR", restored_bgr);
    //cv::waitKey(0);

    //// 3. Разделение на каналы
    std::vector<cv::Mat> channels(3);
    cv::split(ycbcr, channels);

    // Приведение каждого канала к float:
    for (auto& c : channels) {
        c.convertTo(c, CV_32F, 1.0 / 255.0);
    } 
    std::cout << ">>>>> Conversion channels to CV_32F completed" << std::endl;
    // Проверка раздеения на каналы
    //for (int i = 0; i < 3; ++i) {
    //    cv::imshow("TEST " + std::to_string(i), channels[i]);
    //} 
    //cv::waitKey(0);

    cv::Mat& Y = channels[0];
    cv::Mat& Cb = channels[1];
    cv::Mat& Cr = channels[2];
    std::cout << ">>>>> Spliting by channels completed" << std::endl;

    //// Проверка на объединение каналов
    // Перед сборкой обратно в CV_8U
    //for (auto& ch : channels) {
    //    ch.convertTo(ch, CV_8U, 255.0);
    //}
    //cv::Mat ycbcr_restored;
    //cv::merge(channels, ycbcr_restored);
    //cv::imshow("TEST Merging of channels", convert_to_BGR(ycbcr_restored));
    //cv::waitKey(0);

    int width = image.cols;
    int height = image.rows;
    std::cout << ">>>>> Width and Height saved" << std::endl;


    //// 4. Обработка каналов
    std::vector<RLEVector> Y_encoded = processChannel(Y, getStandardLuminanceQuantTable());
    std::cout << ">>> Y_encoded processed" << std::endl;
    std::vector<RLEVector> Cb_encoded = processChannel(Cb, getStandardChrominanceQuantTable());
    std::cout << ">>> Cb_encoded processed" << std::endl;
    std::vector<RLEVector> Cr_encoded = processChannel(Cr, getStandardChrominanceQuantTable());
    std::cout << ">>> Cr_encoded processed" << std::endl;

    std::cout << ">>>>> Channel processed" << std::endl;

    //// 5. Сохранение сжатых данных
    saveCompressed(compressedPath, Y_encoded, Cb_encoded, Cr_encoded, width, height);
    std::cout << ">>>>> Comression completed." << std::endl;

    ////=== ДЕКОМПРЕССИЯ ===
    CompressedImage compressed = loadCompressed(compressedPath);
    std::cout << ">>>>> loadCompressed completed." << std::endl;

    auto restorechannel = [](const CompressedChannel& comp, const cv::Mat& qtable) -> cv::Mat {
        std::vector<cv::Mat> blocks;
        for (const auto& rle : comp.blocks) {
            auto zz = runLengthDecode(rle);
            auto block = zigzagUnscan(zz);
            blocks.push_back(block);
        }
        auto dequant = dequantizeBlocks(blocks, qtable);
        auto idct = applyIDCTToBlocks(dequant);
        decenterBlocks(idct);
        return merge_blocks(idct, comp.width, comp.height, 8);
        };

    ////6. восстановление каналов
    cv::Mat y_restored = restorechannel(compressed.Y, getStandardLuminanceQuantTable());
    cv::Mat cb_restored = restorechannel(compressed.Cb, getStandardChrominanceQuantTable());
    cv::Mat cr_restored = restorechannel(compressed.Cr, getStandardChrominanceQuantTable());
    std::cout << ">>>>> restore channel completed." << std::endl;

    //// 7. объединение каналов
    std::vector<cv::Mat> mergedchannels = { y_restored, cb_restored, cr_restored };
    // Перед сборкой обратно в CV_8U
    for (auto& ch : mergedchannels) {
        ch.convertTo(ch, CV_8U, 255.0);
    }
    cv::Mat ycbcr_restored;
    cv::merge(mergedchannels, ycbcr_restored);
    std::cout << ">>>>> merged channels completed." << std::endl;

    ////8. преобразование в bgr
    cv::Mat restored_bgr = convert_to_BGR(ycbcr_restored);
    std::cout << ">>>>> restored_bgr completed." << std::endl;

    ////9. сохранение восстановленного изображения
    saveImage(restoredPath, restored_bgr);
    std::cout << "Compression and restoration completed" << std::endl;
    return 0;
}
