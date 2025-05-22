#pragma once

#include "compressor.hpp"
#include <fstream>

static void writeChannel(std::ofstream& out, const std::vector<RLEVector>& blocks) {
    int numBlocks = static_cast<int>(blocks.size());
    out.write(reinterpret_cast<char*>(&numBlocks), sizeof(int));

    for (const auto& block : blocks) {
        int length = static_cast<int>(block.size());
        out.write(reinterpret_cast<char*>(&length), sizeof(int));
        for (const auto& pair : block) {
            out.write(reinterpret_cast<const char*>(&pair.first), sizeof(int));
            out.write(reinterpret_cast<const char*>(&pair.second), sizeof(float));
        }
    }
}

static std::vector<RLEVector> readChannel(std::ifstream& in) {
    int numBlocks;
    in.read(reinterpret_cast<char*>(&numBlocks), sizeof(int));
    std::vector<RLEVector> blocks(numBlocks);

    for (int i = 0; i < numBlocks; ++i) {
        int length;
        in.read(reinterpret_cast<char*>(&length), sizeof(int));
        RLEVector block(length);
        for (int j = 0; j < length; ++j) {
            int zeros;
            float value;
            in.read(reinterpret_cast<char*>(&zeros), sizeof(int));
            in.read(reinterpret_cast<char*>(&value), sizeof(float));
            block[j] = { zeros, value };
        }
        blocks[i] = block;
    }

    return blocks;
}

void saveCompressed(const std::string& filename,
    const std::vector<RLEVector>& Y,
    const std::vector<RLEVector>& Cb,
    const std::vector<RLEVector>& Cr,
    int width,
    int height) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::runtime_error("Ошибка открытия файла на запись");

    out.write(reinterpret_cast<char*>(&width), sizeof(int));
    out.write(reinterpret_cast<char*>(&height), sizeof(int));

    writeChannel(out, Y);
    writeChannel(out, Cb);
    writeChannel(out, Cr);

    out.close();
}

CompressedImage loadCompressed(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("Ошибка открытия файла на чтение");

    int width, height;
    in.read(reinterpret_cast<char*>(&width), sizeof(int));
    in.read(reinterpret_cast<char*>(&height), sizeof(int));

    CompressedImage image;
    image.Y.blocks = readChannel(in);
    image.Cb.blocks = readChannel(in);
    image.Cr.blocks = readChannel(in);

    image.Y.width = image.Cb.width = image.Cr.width = width;
    image.Y.height = image.Cb.height = image.Cr.height = height;

    in.close();
    return image;
}