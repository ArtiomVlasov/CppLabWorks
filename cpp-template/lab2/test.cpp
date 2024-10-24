#include <gtest/gtest.h>
#include "hashMap.hpp"

TEST(HashMapTest, TestInsertAndRetrieve) {
    HashMap map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    ASSERT_EQ(map["key1"], "value1");
    ASSERT_EQ(map["key2"], "value2");
    ASSERT_EQ(map.size(), 2);
}

TEST(HashMapTest, TestOverwriteValue) {
    HashMap map;
    map["key1"] = "value1";
    map["key1"] = "new_value1";

    ASSERT_EQ(map["key1"], "new_value1");
    ASSERT_EQ(map.size(), 1);
}

TEST(HashMapTest, TestErase) {
    HashMap map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    ASSERT_EQ(map.erase("key1"), 1);
    ASSERT_FALSE(map.contains("key1"));
    ASSERT_TRUE(map.contains("key2"));
    ASSERT_EQ(map.size(), 1);
    ASSERT_EQ(map.erase("key3"), 0);
    ASSERT_EQ(map.size(), 1);
}

TEST(HashMapTest, TestClear) {
    HashMap map;
    map["key1"] = "value1";
    map["key2"] = "value2";
    map.clear();

    ASSERT_EQ(map.size(), 0);
    ASSERT_FALSE(map.contains("key1"));
    ASSERT_FALSE(map.contains("key2"));
}

TEST(HashMapTest, TestContains) {
    HashMap map;
    map["key1"] = "value1";

    ASSERT_TRUE(map.contains("key1"));
    ASSERT_FALSE(map.contains("key2"));
}

TEST(HashMapTest, TestCopyConstructor) {
    HashMap map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    HashMap copiedMap = map;

    ASSERT_EQ(copiedMap["key1"], "value1");
    ASSERT_EQ(copiedMap["key2"], "value2");
    ASSERT_EQ(copiedMap.size(), 2);
    map["key1"] = "new_value1";
    ASSERT_EQ(copiedMap["key1"], "value1");
}

TEST(HashMapTest, TestAssignmentOperator) {
    HashMap map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    HashMap assignedMap;
    assignedMap = map;

    ASSERT_EQ(assignedMap["key1"], "value1");
    ASSERT_EQ(assignedMap["key2"], "value2");
    ASSERT_EQ(assignedMap.size(), 2);
    map["key1"] = "new_value1";
    ASSERT_EQ(assignedMap["key1"], "value1");
}