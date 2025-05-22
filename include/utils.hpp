#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include <opencv2/opencv.hpp>
#include <vector>

// 1. Загрузка изображения
cv::Mat load_image(const std::string& filename);
void saveImage(const std::string& path, const cv::Mat& image);

// 2. Преобразование в YCbCr
cv::Mat convert_to_YCbCr(const cv::Mat& rgb_image);
cv::Mat convert_to_BGR(const cv::Mat& ycbcr_image);  // на будущее


// 3. Деление каналов на блоки
// Добавления недостающих пикселей изображения, чтобы оно было кратно blockSize
cv::Mat pad_to_block_size(const cv::Mat& channel, int blockSize);
// Деление изображения на блоки 
std::vector<cv::Mat> split_into_blocks(const cv::Mat& channel, int blockSize);
// Объединение блоков в одно изображение
cv::Mat merge_blocks(const std::vector<cv::Mat>& blocks, int width, int height, int blockSize);


// 4. Центрирование значений
void centerBlocks(std::vector<cv::Mat>& blocks);
void decenterBlocks(std::vector<cv::Mat>& blocks);


// 5.
// Применяет дискретное косинусное преобразование (DCT) к блоку 8x8
cv::Mat applyDCT(const cv::Mat& block);
std::vector<cv::Mat> applyDCTToBlocks(const std::vector<cv::Mat>& blocks);
//TODO Реализовать обратные функции
cv::Mat applyIDCT(const cv::Mat& block);
std::vector<cv::Mat> applyIDCTToBlocks(const std::vector<cv::Mat>& blocks);


// 6. Квантование
// Возвращает стандартную таблицу квантования для яркостного канала (Y)
cv::Mat getStandardLuminanceQuantTable();
// Возвращает стандартную таблицу квантования для цветовых каналов (Cb, Cr)
cv::Mat getStandardChrominanceQuantTable();
// Квантование одного блока с помощью таблицы квантования
cv::Mat quantizeBlock(const cv::Mat& block, const cv::Mat& quantTable);
// Квантование всех блоков
std::vector<cv::Mat> quantizeBlocks(const std::vector<cv::Mat>& dctBlocks, const cv::Mat& quantTable);
// Деквантование одного блока
cv::Mat dequantizeBlock(const cv::Mat& block, const cv::Mat& qTable);
// Деквантование вектора блоков
std::vector<cv::Mat> dequantizeBlocks(const std::vector<cv::Mat>& blocks, const cv::Mat& qTable);


// 7. Зигзагообразное сканирование
// Преобразует матрицу 8x8 в вектор длиной 64 (зигзаг-сканирование)
std::vector<float> zigzagScan(const cv::Mat& block);
// Обратное зигзаг-преобразование — из вектора в матрицу 8x8
cv::Mat zigzagUnscan(const std::vector<float>& zigzag);


// 8. RLE
using RLEVector = std::vector<std::pair<int, float>>;
// Кодирование RLE: вход — вектор 64 значений
RLEVector runLengthEncode(const std::vector<float>& input);
// Декодирование RLE: вход — пары (нулей подряд, значение)
std::vector<float> runLengthDecode(const RLEVector& encoded);


// Работа над слоями
std::vector<RLEVector> processChannel(const cv::Mat& channel, const cv::Mat& qTable);


#endif
