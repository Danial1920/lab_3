#include <unordered_map>
#include <list>
#include <stdexcept>
#include <utility>
#include <cstddef>

template <typename Key, typename Value>
class LFUCache {
private:
    struct CacheNode {
        Value value;
        int frequency;
    };

    int capacity_;
    int min_freq_; 

    std::unordered_map<Key, CacheNode> key_to_node_;
    std::unordered_map<int, std::list<Key>> freq_to_list_;

    std::unordered_map<Key, typename std::list<Key>::iterator> key_to_freq_list_iter_;

    /**
     * @brief 
     * @param key 
     */
    void update_frequency(const Key& key) {
        int old_freq = key_to_node_[key].frequency;
        int new_freq = old_freq + 1;

        auto& old_list = freq_to_list_[old_freq];
        auto key_iter = key_to_freq_list_iter_[key];
        old_list.erase(key_iter);

        auto& new_list = freq_to_list_[new_freq];
        new_list.push_front(key);

        key_to_node_[key].frequency = new_freq;
        key_to_freq_list_iter_[key] = new_list.begin();
        
        if (old_list.empty() && old_freq == min_freq_) {
            min_freq_ = new_freq;
        }
    }

public:
    LFUCache(int capacity) : capacity_(capacity), min_freq_(0) {}

    /**
     * @brief 
     * @param key 
     * @return 
     */
    Value get(const Key& key) {
        if (capacity_ <= 0 || key_to_node_.find(key) == key_to_node_.end()) {
            throw std::out_of_range("Key not found in LFU Cache or capacity is zero.");
        }

        Value result = key_to_node_[key].value;
        update_frequency(key);
        return result;
    }

    /**
     * @brief 
     * @param key 
     * @param value 
     */
    void put(const Key& key, const Value& value) {
        if (capacity_ <= 0) {
            return;
        }

        if (key_to_node_.count(key)) {
            key_to_node_[key].value = value;
            update_frequency(key);
            return;
        }

        if (key_to_node_.size() == capacity_) {
            
            auto& list_to_evict = freq_to_list_[min_freq_];
            const Key key_to_evict = list_to_evict.front(); 

            key_to_node_.erase(key_to_evict);
            key_to_freq_list_iter_.erase(key_to_evict);
            list_to_evict.pop_front(); 
        }

        key_to_node_[key] = {value, 1};
        freq_to_list_[1].push_front(key);
        key_to_freq_list_iter_[key] = freq_to_list_[1].begin();
        min_freq_ = 1;
    }
    
    size_t size() const {
        return key_to_node_.size();
    }
};