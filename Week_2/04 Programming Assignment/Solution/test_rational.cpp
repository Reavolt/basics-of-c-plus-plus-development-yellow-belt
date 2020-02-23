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
//class Rational 
//{
//public:
//    Rational() : numer(0), denomin(1)
//    {
//    
//    }
//
//    Rational(int numerator, int denominator) : numer(0), denomin(1)
//    {
//        if (denominator < 0) 
//        {
//            if (numerator < 0) 
//            {
//                denominator = abs(denominator);
//                numerator = abs(numerator);
//            }
//            else 
//            {
//                denominator = abs(denominator);
//                numerator = numerator - 2 * numerator;
//            }
//        }
//
//        if (numerator == 0) 
//        {
//            denominator = 1;
//        }
//
//        int nod_value = nod(numerator, denominator);
//        numer = numerator / nod_value;
//        denomin = denominator / nod_value;
//    }
//
//    int Numerator() const
//    {
//        return numer;
//    }
//
//    int Denominator() const
//    {
//        return denomin;
//    }
//private:
//    int nod(int numerator, int denominator)
//    {
//        return !denominator ? abs(numerator) : nod(denominator, numerator % denominator);
//    }
//private:
//    int numer;
//    int denomin;
//};
//-------------------------------------------------------------------------------------------------
void test_default_consturctor()
{
    assert_equal(Rational().Numerator(), 0, "test Numerator = 0");
    assert_equal(Rational().Denominator(), 1, "test Denominator = 1");
}
//-------------------------------------------------------------------------------------------------
void test_irreducible_fraction()
{
    assert_equal(Rational(1,1).Numerator(), 1, "test 1/1 -> 1/1");
    assert_equal(Rational(1,1).Denominator(), 1, "test 1/1 -> 1/1");
    assert_equal(Rational(5,7).Numerator(), 5, "test 5/7 -> 5/7");
    assert_equal(Rational(5,7).Denominator(), 7, "test 5/7 -> 5/7");
}
//-------------------------------------------------------------------------------------------------
void test_zero_numenator() 
{
    assert_equal(Rational(0,25).Numerator(), 0, "test 0/25 -> 0/1");
    assert_equal(Rational(0,25).Denominator(), 1, "test 0/25 -> 0/1");
}
//-------------------------------------------------------------------------------------------------
void test_both_negative()
{
    assert_equal(Rational(-2,-3).Numerator(), 2, "test -2/-3 -> 2/3");
    assert_equal(Rational(-2,-3).Denominator(), 3, "test -2/-3 -> 2/3");
    assert_equal(Rational(-6,-12).Numerator(), 1, "test -6/-12 -> 1/2");
    assert_equal(Rational(-6,-12).Denominator(), 2, "test -6/-12 -> 1/2");
}
//-------------------------------------------------------------------------------------------------
void test_negative_denominator()
{
    assert_equal(Rational(6,-12).Numerator(), -1, "test 6/-12 -> -1/2");
    assert_equal(Rational(6,-12).Denominator(), 2, "test -6/-12 -> -1/2");
}
//-------------------------------------------------------------------------------------------------
void test_negative_numerator()
{
    assert_equal(Rational(-3,12).Numerator(), -1, "test -3/12 -> -1/4");
    assert_equal(Rational(-3,12).Denominator(), 4, "test -3/12 -> -1/4");
}
//-------------------------------------------------------------------------------------------------
void test_fraction_reduction()
{
    assert_equal(Rational(24,64).Numerator(), 3, "test 24/64 -> 3/8");
    assert_equal(Rational(24,64).Denominator(), 8, "test 24/64 -> 3/8");
    assert_equal(Rational(2,4).Numerator(), 1, "test 2/4 -> 1/2");
    assert_equal(Rational(2,4).Denominator(), 2, "test 2/4 -> 1/2");
}
//-------------------------------------------------------------------------------------------------
int main() 
{
    test_runner runner;
    runner.run_test(test_default_consturctor, "test_rational");
    runner.run_test(test_irreducible_fraction, "test_irreducible_fraction");
    runner.run_test(test_zero_numenator, "test_zero_numenator");
    runner.run_test(test_both_negative, "test_both_negative");
    runner.run_test(test_negative_denominator, "test_negative_denominator");
    runner.run_test(test_negative_numerator, "test_negative_numerator");
    runner.run_test(test_fraction_reduction, "test_fraction_reduction");

    return 0;
}
//-------------------------------------------------------------------------------------------------