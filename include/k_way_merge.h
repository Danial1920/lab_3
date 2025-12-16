#include <vector>
#include <queue>
#include <iostream>
#include <functional> 

struct HeapNode {
    int value;
    int list_index;   
    int element_index; 

    bool operator>(const HeapNode& other) const {
        return value > other.value;
    }
};

/**
 * @brief 
 * @param lists 
 * @return
 */
std::vector<int> KWayMerge(const std::vector<std::vector<int>>& lists) {
    std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> min_heap;
    std::vector<int> result;
    
    for (size_t i = 0; i < lists.size(); ++i) {
        if (!lists[i].empty()) {
            min_heap.push(HeapNode{
                lists[i][0], 
                static_cast<int>(i), 
                1                   
            });
        }
    }

    while (!min_heap.empty()) {
        HeapNode current = min_heap.top();
        min_heap.pop();

        result.push_back(current.value);

        int next_element_index = current.element_index;
        int list_idx = current.list_index;
    
        int list_size = static_cast<int>(lists[list_idx].size());

        if (next_element_index < list_size) {
            min_heap.push(HeapNode{
                lists[list_idx][next_element_index], 
                list_idx,                           
                next_element_index + 1               
            });
        }
    }

    return result;
}