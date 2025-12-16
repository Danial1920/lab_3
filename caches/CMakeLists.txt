

add_executable(
  lfu_cache_tests
  lfu_cache_test.cpp
)

target_link_libraries(
  lfu_cache_tests
  PRIVATE GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(lfu_cache_tests)