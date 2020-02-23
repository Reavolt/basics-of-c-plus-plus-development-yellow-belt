#include <iostream>
#include <sstream>
#include <set>
#include <map>
//-------------------------------------------------------------------------------------------------
//Unit test framework
template <typename T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) 
{
    os << "{";
    bool first = true;
    for (const auto& x : s) 
    {
        if (!first) 
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}
//-------------------------------------------------------------------------------------------------
template <typename Key, typename Value>
std::ostream& operator << (std::ostream& os, const std::map<Key, Value>& map)
{
    os << "{";
    bool first = true;
    for (const auto& kv : map)
    {
        if (!first) 
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}
//-------------------------------------------------------------------------------------------------
template<typename T, typename U>
void assert_equal(const T& t, const U& u, const std::string& hint)
{
    if (t != u) 
    {
        std::ostringstream os;
        os << " Assertion failed: " << t << " != " << u << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}
//-------------------------------------------------------------------------------------------------
inline void Assert(bool b, const std::string& hint) 
{
    assert_equal(b, true, hint);
}
//-------------------------------------------------------------------------------------------------
class test_runner 
{
public:
    template <class test_func>
    void run_test(test_func func, const std::string& test_name)
    {
        try 
        {
            func();
            std::cerr << "PASSED: " << test_name << std::endl;
        }
        catch (std::runtime_error & e)
        {
            ++fail_count;
            std::cerr << "FAIL: " << test_name << e.what() << std::endl;
        }
    }

    ~test_runner()
    {
        if (fail_count > 0) 
        {
            std::cerr << "-------------------------------------------" << std::endl;
            std::cerr << "FAILED (failures = " << fail_count << ")" << std::endl;
            exit(1);
        }
        else
        {
            std::cerr << "-------------------------------------------" << std::endl;
            std::cerr << "OK" << std::endl;
        }
    }
private:
    int fail_count = 0;
};
//-------------------------------------------------------------------------------------------------
bool IsPalindrom(const std::string& str) 
{
    return std::equal(str.begin(), str.begin() + str.size() / 2, str.rbegin());
}
//-------------------------------------------------------------------------------------------------
void test_is_palindrome()
{
    Assert(IsPalindrom(""), "empty string ->> palindrome");
    Assert(IsPalindrom("c"), "c string ->> palindrome");
    Assert(IsPalindrom("aca"), "aca string ->> palindrome");
    Assert(IsPalindrom("acdca"), "acdca string ->> palindrome");
    Assert(IsPalindrom("AccA"), "AcсA string ->> palindrome");
    Assert(IsPalindrom("caZaZac"), "caZaZac string ->> palindrome");
    Assert(IsPalindrom("++C++"), "++C++ string ->> palindrome");
    Assert(IsPalindrom("aBCBa"), "c string ->> palindrome");
    Assert(IsPalindrom("   aBCBa   "), "   aBCBa    string ->> palindrome");
    Assert(IsPalindrom("   aBcBa   "), "   aBcBa    string ->> palindrome");
    Assert(IsPalindrom("a B c B a"), "a B c B a string ->> palindrome");
    Assert(IsPalindrom("MalayalaM"), "MalayalaM string ->> palindrome");
    Assert(IsPalindrom("\t\n  \n\t"), "\t\n  \n\t string ->> palindrome");
    Assert(IsPalindrom("abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba"), 
	"abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba string ->> palindrome");

    Assert(!IsPalindrom("VC"), "VC string != palindrome");
    Assert(!IsPalindrom("VVddVC"), "VVddVC string != palindrome");
    Assert(!IsPalindrom("VVddCV"), "VVddCV string != palindrome");
    Assert(!IsPalindrom("VCddVV"), "VCddVC string != palindrome");
    Assert(!IsPalindrom("CVddVV"), "CVddVV string != palindrome");
    Assert(!IsPalindrom("cvDdvc"), "cvDdvc string != palindrome");
    Assert(!IsPalindrom("cvdDvc"), "cvdDvc string != palindrome");
    Assert(!IsPalindrom("Cvddvc"), "CvdDvc string != palindrome");
    Assert(!IsPalindrom("cvddvC"), "cvddvC string != palindrome");
    Assert(!IsPalindrom("cvddVc"), "cvddVc string != palindrome");
    Assert(!IsPalindrom("cVddvc"), "cvddVc string != palindrome");
    Assert(!IsPalindrom("abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcbb"), 
	"aaaaaabcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcbaaaaaadcccccccccc string != palindrome");
    Assert(!IsPalindrom("   CVddVC"), "   CVvdVC string != palindrome");
    Assert(!IsPalindrom("CVddVC   "), "CVvdVC    string != palindrome");
}
//-------------------------------------------------------------------------------------------------
int main() 
{
    test_runner runner;
    runner.run_test(test_is_palindrome, "test_is_palindrome");
    return 0;
}
//-------------------------------------------------------------------------------------------------