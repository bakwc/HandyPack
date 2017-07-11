#include "saveload.h"

#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>


using namespace NSaveLoad;

TEST(SaveLoadTest, podTypes) {
    std::stringstream out;
    int8_t ti8 = -1;
    uint8_t tui8 = 2;
    int16_t ti16 = -3;
    uint16_t tui16 = 4;
    int32_t ti32 = -5;
    uint32_t tui32 = 6;
    int32_t ti64 = -7;
    uint32_t tui64 = 8;

    Save(out, ti8);
    Save(out, tui8);
    Save(out, ti16, tui16);
    Save(out, ti32, tui32, ti64, tui64);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    ti8 = 0;
    tui8 = 0;
    ti16 = 0;
    tui16 = 0;
    ti32 = 0;
    tui32 = 0;
    ti64 = 0;
    tui64 = 0;

    Load(in, ti8);
    Load(in, tui8);
    Load(in, ti16, tui16);
    Load(in, ti32, tui32, ti64, tui64);

    ASSERT_EQ(ti8, -1);
    ASSERT_EQ(tui8, 2);
    ASSERT_EQ(ti16, -3);
    ASSERT_EQ(tui16, 4);
    ASSERT_EQ(ti32, -5);
    ASSERT_EQ(tui32, 6);
    ASSERT_EQ(ti64, -7);
    ASSERT_EQ(tui64, 8);
}

struct TSimpleStruct {
    int A;
    uint32_t B;
    uint64_t C;
    double D;
    float E;

    SAVELOAD(A, B, C, D, E)
};

TEST(SaveLoadTest, simpleStruct) {
    TSimpleStruct test;
    test.A = 1;
    test.B = 2;
    test.C = 3;
    test.D = 4;
    test.E = 5;

    std::stringstream out;
    Save(out, test);
    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    TSimpleStruct unpacked;
    Load(in, unpacked);

    ASSERT_EQ(unpacked.A, 1);
    ASSERT_EQ(unpacked.B, 2);
    ASSERT_EQ(unpacked.C, 3);
    ASSERT_EQ(unpacked.D, 4);
    ASSERT_EQ(unpacked.E, 5);
}

TEST(SaveLoadTest, vectorTest) {
    std::vector<int> nums, unpacked;
    nums.push_back(10);
    nums.push_back(30);
    nums.push_back(50);

    std::stringstream out;
    Save(out, nums);
    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, unpacked);

    ASSERT_EQ(unpacked.size(), 3);
    ASSERT_EQ(unpacked[0], 10);
    ASSERT_EQ(unpacked[1], 30);
    ASSERT_EQ(unpacked[2], 50);
}

TEST(SaveLoadTest, vectorTest2) {
    std::vector<TSimpleStruct> vec, unpacked;
    TSimpleStruct a,b;
    a.A = 10;
    b.B = 20;

    vec.push_back(a);
    vec.push_back(b);

    std::stringstream out;
    Save(out, vec);
    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, unpacked);

    ASSERT_EQ(unpacked.size(), 2);
    ASSERT_EQ(unpacked[0].A, 10);
    ASSERT_EQ(unpacked[1].B, 20);
}

struct TStructWithString {
    std::string A;
    int B;

    SAVELOAD(A, B)
};

TEST(SaveLoadTest, vectorTest3) {
    std::vector<TStructWithString> vec, unpacked;
    TStructWithString a,b;
    a.A = "hello world";
    b.B = 20;

    vec.push_back(a);
    vec.push_back(b);

    std::stringstream out;
    Save(out, vec);
    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, unpacked);

    ASSERT_EQ(unpacked.size(), 2);
    ASSERT_EQ(unpacked[0].A, "hello world");
    ASSERT_EQ(unpacked[1].B, 20);
}

TEST(SaveLoadTest, mapTest) {
    std::map<std::string, int> m1, m2;
    m1["hello"] = 42;
    m1["world"] = 39;

    std::stringstream out;
    Save(out, m1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, m2);

    ASSERT_EQ(m2["hello"], 42);
    ASSERT_EQ(m2["world"], 39);
}

TEST(SaveLoadTest, unorderedMapTest) {
    std::unordered_map<std::string, int> m1, m2;
    m1["hello"] = 42;
    m1["world"] = 39;

    std::stringstream out;
    Save(out, m1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, m2);

    ASSERT_EQ(m2["hello"], 42);
    ASSERT_EQ(m2["world"], 39);
}

TEST(SaveLoadTest, setTest) {
    std::set<int> s1, s2;
    s1.insert(10);
    s1.insert(20);
    s1.insert(50);

    std::stringstream out;
    Save(out, s1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, s2);

    ASSERT_TRUE(s2.find(10) != s2.end());
    ASSERT_TRUE(s2.find(20) != s2.end());
    ASSERT_TRUE(s2.find(50) != s2.end());
    ASSERT_TRUE(s2.find(100) == s2.end());
}

TEST(SaveLoadTest, unorderedSetTest) {
    std::unordered_set<int> s1, s2;
    s1.insert(10);
    s1.insert(20);
    s1.insert(50);

    std::stringstream out;
    Save(out, s1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, s2);

    ASSERT_TRUE(s2.find(10) != s2.end());
    ASSERT_TRUE(s2.find(20) != s2.end());
    ASSERT_TRUE(s2.find(50) != s2.end());
    ASSERT_TRUE(s2.find(100) == s2.end());
}
