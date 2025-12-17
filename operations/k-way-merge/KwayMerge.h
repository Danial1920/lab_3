#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

template<typename T>
struct MergeElement {
    T value;
    size_t block_idx;
    size_t element_idx;

    bool operator>(const MergeElement& other) const {
        return value > other.value;
    }
};

template<typename T>
std::vector<T> KwayMergeSort(const std::vector<T>& array
    , std::size_t k = 4
    , std::size_t block_size = 8)
{
    if (array.empty()) return {};
    if (array.size() <= 1) return array;

    std::vector<std::vector<T>> blocks;
    for (size_t i = 0; i < array.size(); i += block_size) {
        size_t end = std::min(i + block_size, array.size());
        std::vector<T> block(array.begin() + i, array.begin() + end);
        std::sort(block.begin(), block.end());
        blocks.push_back(block);
    }

    std::vector<T> result;
    result.reserve(array.size());
    
    std::priority_queue<MergeElement<T>, std::vector<MergeElement<T>>, std::greater<MergeElement<T>>> pq;

    for (size_t i = 0; i < blocks.size(); ++i) {
        if (!blocks[i].empty()) {
            pq.push({blocks[i][0], i, 0});
        }
    }

    while (!pq.empty()) {
        MergeElement<T> current = pq.top();
        pq.pop();
        result.push_back(current.value);

        if (current.element_idx + 1 < blocks[current.block_idx].size()) {
            pq.push({
                blocks[current.block_idx][current.element_idx + 1],
                current.block_idx,
                current.element_idx + 1
            });
        }
    }

    return result;
}