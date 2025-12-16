#include "gtest/gtest.h"
#include "lfu_cache.h"
#include <stdexcept>

using IntLFUCache = LFUCache<int, int>;

TEST(LFUCacheTest, BasicPutAndGet) {
    IntLFUCache cache(2);
    
    cache.put(1, 10); 
    cache.put(2, 20); 

    ASSERT_EQ(cache.get(1), 10); 

    ASSERT_EQ(cache.size(), 2);
}

TEST(LFUCacheTest, LFU_Eviction) {
    IntLFUCache cache(2);
    
    cache.put(1, 10); 
    cache.put(2, 20); 
    cache.get(1);
    

    cache.put(3, 30); 
    
    ASSERT_EQ(cache.size(), 2);
    ASSERT_THROW(cache.get(2), std::out_of_range);
    ASSERT_EQ(cache.get(1), 10);
    ASSERT_EQ(cache.get(3), 30); 
}

TEST(LFUCacheTest, LFU_LRU_TieBreaking) {
    IntLFUCache cache(3);
    
    cache.put(1, 10); 
    cache.put(2, 20); 
    cache.put(3, 30); 

    cache.get(1);
    
    
    cache.put(4, 40); 
    ASSERT_THROW(cache.get(3), std::out_of_range);
    ASSERT_EQ(cache.get(2), 20); 
    ASSERT_EQ(cache.get(4), 40); 
}

TEST(LFUCacheTest, UpdateValueAndFrequency) {
    IntLFUCache cache(1);
    
    cache.put(1, 10); 
    
    cache.put(1, 100); 

    ASSERT_EQ(cache.get(1), 100); 
}

TEST(LFUCacheTest, ZeroCapacity) {
    IntLFUCache cache(0);
    
    cache.put(1, 10); 
    ASSERT_EQ(cache.size(), 0);
    ASSERT_THROW(cache.get(1), std::out_of_range);
}