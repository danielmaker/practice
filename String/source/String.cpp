#include <iostream>
#include <vector>
#include <string.h>

class String
{
public:
    String()
    {
        data.push_back(0);
    }

    String(const char* str)
    {
        int n = strlen(str);
        data.resize(n+1);
        for (int i = 0; i < n; ++i)
        {
            data[i] = str[i];
        }
    }

    const char& at (size_t pos) const  { return data[pos]; }
    const char& operator[] (size_t pos) const { return data[pos]; }

    String& operator+=(const String& rhs)
    {
        data.reserve(data.size() + rhs.size());
        data.insert(data.end()-1, rhs.data.begin(), rhs.data.end()-1);
        return *this;
    }

    String operator+(const String& rhs) const
    {
        String tmp(*this);
        tmp += rhs;
        return tmp;
    }

    int compare (const String& str) const
    {
        return strcmp(c_str(), str.c_str());
    }

    const char* c_str() const { return &data[0]; }

    size_t size() const { return data.size() - 1; }
    size_t length() const {return size(); }
    bool empty() const  { return 0 == size(); }

protected:
    std::vector<char> data;  // a character array ending with zero
};


// ------------------------------------------------------------------------------
bool operator== (const String& lhs, const String& rhs)
{
    return 0 == strcmp(lhs.c_str(), rhs.c_str());
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    for (int i = 0; i < str.size(); ++i)
    {
        os << str[i];
    }
    return os;
}


// ------------------------------------------------------------------------------
#include <gtest/gtest.h>
#include <string>

TEST(TestCase, size_test)
{
    String s1("Hello");
    EXPECT_EQ(s1.size(), 5);
    EXPECT_EQ(s1.length(), 5);
    EXPECT_EQ(s1.empty(), false);

    String s2;
    EXPECT_EQ(s2.size(), 0);
    EXPECT_EQ(s2.length(), 0);
    EXPECT_EQ(s2.empty(), true);
}

TEST(TestCase, operator_eq_test)
{
    String s1("Hello");
    EXPECT_TRUE(s1 == "Hello");
}

TEST(TestCase, operator_add_test)
{
    String s1("Hello");
    String s2("World");
    String s3 = s1 + " " + s2;

    EXPECT_EQ(s3, "Hello World");
}

TEST(TestCase, ostream_test)
{
    String s1("Hello");
    String s2("World");

    std::string output;
    std::ostringstream oss;
    oss << s1 + " " + s2 << std::endl;
    // std::cout << s1 + " " + s2 << std::endl;

    EXPECT_EQ(oss.str(), "Hello World\n");
    // std::cout << oss.str();
}
