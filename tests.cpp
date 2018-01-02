#include "handypack.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <tuple>


using namespace NHandyPack;

TEST(HandyPackTest, podTypes) {
    std::stringstream out;
    int8_t ti8 = -1;
    uint8_t tui8 = 2;
    int16_t ti16 = -3;
    uint16_t tui16 = 4;
    int32_t ti32 = -5;
    uint32_t tui32 = 6;
    int32_t ti64 = -7;
    uint32_t tui64 = 8;

    Dump(out, ti8);
    Dump(out, tui8);
    Dump(out, ti16, tui16);
    Dump(out, ti32, tui32, ti64, tui64);

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

    HANDYPACK(A, B, C, D, E)
};

TEST(HandyPackTest, simpleStruct) {
    TSimpleStruct test;
    test.A = 1;
    test.B = 2;
    test.C = 3;
    test.D = 4;
    test.E = 5;

    std::stringstream out;
    Dump(out, test);
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

TEST(HandyPackTest, vectorTest) {
    std::vector<int> nums, unpacked;
    nums.push_back(10);
    nums.push_back(30);
    nums.push_back(50);

    std::stringstream out;
    Dump(out, nums);
    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, unpacked);

    ASSERT_EQ(unpacked.size(), 3);
    ASSERT_EQ(unpacked[0], 10);
    ASSERT_EQ(unpacked[1], 30);
    ASSERT_EQ(unpacked[2], 50);
}

TEST(HandyPackTest, vectorTest2) {
    std::vector<TSimpleStruct> vec, unpacked;
    TSimpleStruct a,b;
    a.A = 10;
    b.B = 20;

    vec.push_back(a);
    vec.push_back(b);

    std::stringstream out;
    Dump(out, vec);
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

    HANDYPACK(A, B)
};

TEST(HandyPackTest, vectorTest3) {
    std::vector<TStructWithString> vec, unpacked;
    TStructWithString a,b;
    a.A = "hello world";
    b.B = 20;

    vec.push_back(a);
    vec.push_back(b);

    std::stringstream out;
    Dump(out, vec);
    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, unpacked);

    ASSERT_EQ(unpacked.size(), 2);
    ASSERT_EQ(unpacked[0].A, "hello world");
    ASSERT_EQ(unpacked[1].B, 20);
}

TEST(HandyPackTest, mapTest) {
    std::map<std::string, int> m1, m2;
    m1["hello"] = 42;
    m1["world"] = 39;

    std::stringstream out;
    Dump(out, m1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, m2);

    ASSERT_EQ(m2["hello"], 42);
    ASSERT_EQ(m2["world"], 39);
}

TEST(HandyPackTest, unorderedMapTest) {
    std::unordered_map<std::string, int> m1, m2;
    m1["hello"] = 42;
    m1["world"] = 39;

    std::stringstream out;
    Dump(out, m1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, m2);

    ASSERT_EQ(m2["hello"], 42);
    ASSERT_EQ(m2["world"], 39);
}

TEST(HandyPackTest, setTest) {
    std::set<int> s1, s2;
    s1.insert(10);
    s1.insert(20);
    s1.insert(50);

    std::stringstream out;
    Dump(out, s1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, s2);

    ASSERT_TRUE(s2.find(10) != s2.end());
    ASSERT_TRUE(s2.find(20) != s2.end());
    ASSERT_TRUE(s2.find(50) != s2.end());
    ASSERT_TRUE(s2.find(100) == s2.end());
}

TEST(HandyPackTest, unorderedSetTest) {
    std::unordered_set<int> s1, s2;
    s1.insert(10);
    s1.insert(20);
    s1.insert(50);

    std::stringstream out;
    Dump(out, s1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, s2);

    ASSERT_TRUE(s2.find(10) != s2.end());
    ASSERT_TRUE(s2.find(20) != s2.end());
    ASSERT_TRUE(s2.find(50) != s2.end());
    ASSERT_TRUE(s2.find(100) == s2.end());
}

TEST(HandyPackTest, tupletest) {
    std::tuple<uint32_t, int8_t, std::string> t1(42, -3, "test");
    std::tuple<uint32_t, int8_t, std::string> t2;

    std::stringstream out;
    Dump(out, t1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, t2);

    ASSERT_EQ(std::get<0>(t2), 42);
    ASSERT_EQ(std::get<1>(t2), -3);
    ASSERT_EQ(std::get<2>(t2), "test");
}

TEST(HandyPackTest, wstringtest) {
    std::wstring s1 = L"test_wide_string ыыы";
    std::wstring s2;

    std::stringstream out;
    Dump(out, s1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, s2);

    ASSERT_EQ(s1, s2);
}

TEST(HandyPackTest, wstringUnorderedMap) {
    std::unordered_map<std::wstring, uint32_t> m1, m2;
    m1[L"test_wide_string ыыы"] = 13;
    m1[L"someTest"] = 42;

    std::stringstream out;
    Dump(out, m1);

    std::string data = out.str();
    imemstream in(data.c_str(), data.size());

    Load(in, m2);

    ASSERT_EQ(m2[L"someTest"], 42);
    ASSERT_EQ(m2[L"test_wide_string ыыы"], 13);
}
