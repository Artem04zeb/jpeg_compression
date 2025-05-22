#pragma once

#include "utils.hpp"

RLEVector runLengthEncode(const std::vector<float>& input) {
    RLEVector encoded;

    // явно сохран€ем DC
    encoded.emplace_back(0, input[0]);

    int zeroCount = 0;
    for (size_t i = 1; i < input.size(); ++i) {
        if (input[i] == 0) {
            ++zeroCount;
        }
        else {
            encoded.emplace_back(zeroCount, input[i]);
            zeroCount = 0;
        }
    }

    encoded.emplace_back(0, 0); // EOB
    return encoded;
}

std::vector<float> runLengthDecode(const RLEVector& encoded) {
    std::vector<float> result;
    result.push_back(encoded.empty() ? 0 : encoded[0].second); // DC-коэффициент

    for (size_t i = 1; i < encoded.size(); ++i) {
        int zeros = encoded[i].first;
        float value = encoded[i].second;

        if (zeros == 0 && value == 0) break; // EOBz

        result.insert(result.end(), zeros, 0);
        result.push_back(value);
    }

    // ƒополнить до 64 значений, если не хватает
    while (result.size() < 64) {
        result.push_back(0);
    }

    return result;
}
