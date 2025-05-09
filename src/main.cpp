#include <opencv2/opencv.hpp>
#include "utils.hpp"
#include <string>
#include <vector>


int main() {

    std::string inputPath = "D:\\Desktop\\курсовая работа\\data\\input.jpg";

    // Считывание изображения
    cv::Mat img = load_image(inputPath);
    //cv::imshow("test", img);
    //cv::waitKey(0);

    // Проверка работы конвертера
    cv::Mat ycbcr = convert_to_YCbCr(img);
    //cv::imshow("test", ycbcr);
    //cv::waitKey(0);

    // Проверка работы функции
    //cv::Mat new_image = pad_to_block_size(img, 8);
    //std::cout << (new_image.rows) << std::endl;
    //std::cout << (new_image.cols) << std::endl;
    //cv::imshow("YCbCr", img);

    // Проверка работы функции
    //std::vector<cv::Mat> splitted = split_into_blocks(new_image, 200); // 8
    //std::cout << (splitted[0].rows) << std::endl;
    //std::cout << (splitted[0].cols) << std::endl;
    //cv::imshow("YCbCr", splitted[0]);
    //cv::imshow("YCbCr2", splitted[1]);
    //cv::imshow("YCbCr3", splitted[2]);
    //cv::waitKey(0);

    // Проверка работы центрирования и децентрирования
    //TODO Почему-то при центрирование+децентрирование не дает начальную картинку
    std::vector<cv::Mat> test_case;
    test_case.push_back(img);
    std::cout << "ASD ASD" << std::endl;
    centerBlocks(test_case);
    decenterBlocks(test_case);
    cv::imshow("YCbCr3", test_case[0]);
    cv::waitKey(0);


}
