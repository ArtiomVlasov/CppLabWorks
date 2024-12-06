#include <gtest/gtest.h>
#include "hashMap.hpp"

TEST(HashMapTest, TestInsertAndRetrieve) {
    HashMap<std::string, std::string> map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    ASSERT_EQ(map["key1"], "value1");
    ASSERT_EQ(map["key2"], "value2");
    ASSERT_EQ(map.size(), 2);
}

TEST(HashMapTest, TestOverwriteValue) {
    HashMap<std::string, std::string> map;
    map["key1"] = "value1";
    map["key1"] = "new_value1";

    ASSERT_EQ(map["key1"], "new_value1");
    ASSERT_EQ(map.size(), 1);
}

TEST(HashMapTest, TestErase) {
    HashMap<std::string, std::string> map;
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
    HashMap<std::string, std::string> map;
    map["key1"] = "value1";
    map["key2"] = "value2";
    map.clear();

    ASSERT_EQ(map.size(), 0);
    ASSERT_FALSE(map.contains("key1"));
    ASSERT_FALSE(map.contains("key2"));
}

TEST(HashMapTest, TestContains) {
    HashMap<std::string, std::string> map;
    map["key1"] = "value1";

    ASSERT_TRUE(map.contains("key1"));
    ASSERT_FALSE(map.contains("key2"));
}

TEST(HashMapTest, TestCopyConstructor) {
    HashMap<std::string, std::string> map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    HashMap<std::string, std::string> copiedMap = map;

    ASSERT_EQ(copiedMap["key1"], "value1");
    ASSERT_EQ(copiedMap["key2"], "value2");
    ASSERT_EQ(copiedMap.size(), 2);
    map["key1"] = "new_value1";
    ASSERT_EQ(copiedMap["key1"], "value1");
}

TEST(HashMapTest, TestAssignmentOperator) {
    HashMap<std::string, std::string> map;
    map["key1"] = "value1";
    map["key2"] = "value2";

    HashMap<std::string, std::string> assignedMap;
    assignedMap = map;

    ASSERT_EQ(assignedMap["key1"], "value1");
    ASSERT_EQ(assignedMap["key2"], "value2");
    ASSERT_EQ(assignedMap.size(), 2);
    map["key1"] = "new_value1";
    ASSERT_EQ(assignedMap["key1"], "value1");
}

TEST(HashMapTest, TestDifferentKeyAndValueTypes) {
    HashMap<int, double> map;
    map[1] = 1.1;
    map[2] = 2.2;

    ASSERT_EQ(map[1], 1.1);
    ASSERT_EQ(map[2], 2.2);
    ASSERT_EQ(map.size(), 2);

    map[1] = 3.3;
    ASSERT_EQ(map[1], 3.3);
}
