#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <cmath>

//-------------------------------------------------------------------------------------------------
//Unit test framework
template <class T>
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
template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) 
{
    os << "{";
    bool first = true;
    for (const auto& kv : m) 
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
template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint)
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
    AssertEqual(b, true, hint);
}
//-------------------------------------------------------------------------------------------------
class TestRunner 
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name)
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

    ~TestRunner() 
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
int GetDistinctRealRootCount(double a, double b, double c) 
{
    double D = std::pow(b, 2) - 4 * a * c;

    if (a == 0)
    {
        if (b != 0)
        {
            std::cout << -c / b << std::endl;
            return 1;
        }
    }
    else
    if (D == 0)
    {
        std::cout << -b / (2 * a) << std::endl;
        return 1;
    }
    else
    if (D > 0)
    {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        std::cout << x1 << " " << x2 << std::endl;
        return 2;
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------
void test_no_roots() 
{
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "test_1_no_roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "test_2_no_roots");
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "test_3_no_roots");
}
//-------------------------------------------------------------------------------------------------
void test_linear_equation()
{
    AssertEqual(GetDistinctRealRootCount(0, -1, 12), 1, "test_1_linear_equation");
    AssertEqual(GetDistinctRealRootCount(0, 123, 44), 1, "test_2_linear_equation");
    AssertEqual(GetDistinctRealRootCount(0, 23, -12), 1, "test_3_linear_equation");
}
//-------------------------------------------------------------------------------------------------
void test_positive_discriminant()
{
    AssertEqual(GetDistinctRealRootCount(1, 5, 4), 2, "test_1_positive_discriminant");
    AssertEqual(GetDistinctRealRootCount(4, 2, -1), 2, "test_2_positive_discriminant");
    AssertEqual(GetDistinctRealRootCount(-2, 4, -1), 2, "test_3_positive_discriminant");
}
//-------------------------------------------------------------------------------------------------
void test_zero_discriminant()
{
    AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "test_1_zero_discriminant");
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, "test_2_zero_discriminant");
    AssertEqual(GetDistinctRealRootCount(16, 8, 1), 1, "test_3_zero_discriminant");
}
//-------------------------------------------------------------------------------------------------
void test_negative_discriminant()
{
    AssertEqual(GetDistinctRealRootCount(9, 6, 2), 0, "test_1_negative_discriminant");
    AssertEqual(GetDistinctRealRootCount(-7, -3, -2), 0, "test_2_negative_discriminant");
    AssertEqual(GetDistinctRealRootCount(4, 4, 4), 0, "test_3_negative_discriminant");
}
//-------------------------------------------------------------------------------------------------
int main() 
{
    TestRunner runner;
    runner.RunTest(test_no_roots, "test_no_roots");
    runner.RunTest(test_linear_equation, "test_linear_equation");
    runner.RunTest(test_positive_discriminant, "test_positive_discriminant");
    runner.RunTest(test_zero_discriminant, "test_zero_discriminant");
    runner.RunTest(test_negative_discriminant, "test_negative_discriminant");
    return 0;
}
//-------------------------------------------------------------------------------------------------