#include "gtest/gtest.h"
#include "k_way_merge.h" // Подключаем ваш реализованный заголовок

// Используем TEST для создания тестового случая
TEST(KWayMergeTest, BasicMerge) {
    // Сценарий: Базовое слияние трех отсортированных списков.
    std::vector<std::vector<int>> inputs = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int> result = KWayMerge(inputs);

    // ASSERT_EQ проверяет, что векторы равны по содержимому и порядку.
    ASSERT_EQ(result, expected) << "Ошибка при базовом слиянии.";
}

TEST(KWayMergeTest, EmptyAndSingleLists) {
    // Сценарий: Слияние, включающее пустой список и список с одним элементом.
    std::vector<std::vector<int>> inputs = {
        {10},       // Список с одним элементом
        {},         // Пустой список
        {1, 5, 15}  // Обычный список
    };
    std::vector<int> expected = {1, 5, 10, 15};

    std::vector<int> result = KWayMerge(inputs);

    ASSERT_EQ(result, expected) << "Ошибка при обработке пустых и одиночных списков.";
}

TEST(KWayMergeTest, HandlingDuplicates) {
    // Сценарий: Списки с повторяющимися элементами.
    std::vector<std::vector<int>> inputs = {
        {1, 1, 5},
        {2, 5, 8},
        {1, 6, 6}
    };
    // Все дубликаты должны быть сохранены в правильном порядке
    std::vector<int> expected = {1, 1, 1, 2, 5, 5, 6, 6, 8};

    std::vector<int> result = KWayMerge(inputs);

    ASSERT_EQ(result, expected) << "Ошибка при обработке дубликатов.";
}

TEST(KWayMergeTest, AlreadyMerged) {
    // Сценарий: Списки, которые уже идут в последовательном порядке.
    std::vector<std::vector<int>> inputs = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    std::vector<int> expected = {1, 2, 3, 4, 5, 6};

    std::vector<int> result = KWayMerge(inputs);

    ASSERT_EQ(result, expected) << "Ошибка при уже отсортированных списках.";
}

TEST(KWayMergeTest, OneLargeList) {
    // Сценарий: Вектор содержит только один список.
    std::vector<std::vector<int>> inputs = {
        {10, 20, 30, 40, 50}
    };
    std::vector<int> expected = {10, 20, 30, 40, 50};

    std::vector<int> result = KWayMerge(inputs);

    ASSERT_EQ(result, expected) << "Ошибка при слиянии одного списка.";
}