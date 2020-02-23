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
//class Person
//{
//public:
//    void ChangeFirstName(int year, const std::string& first_name)
//    {
//        // добавить факт изменения имени на first_name в год year
//        first_names[year] = first_name;
//    }
//
//    void ChangeLastName(int year, const std::string& last_name)
//    {
//        // добавить факт изменения фамилии на last_name в год year
//        last_names[year] = last_name;
//    }
//
//    std::string GetFullName(int year)
//    {
//        // получить имя и фамилию по состоянию на конец года year
//        const std::string first_name = GetFirstName(year, first_names);
//        const std::string last_name = GetLastName(year, last_names);
//        std::string full_name = first_name + " " + last_name;
//
//        if (first_name.size() == 0 && last_name.size() == 0)
//        {
//            full_name = "Incognito";
//            return full_name;
//        }
//        else
//        if (first_name.size() == 0)
//        {
//            full_name = last_name + " with unknown first name";
//            return full_name;
//        }
//        else
//        if (last_name.size() == 0)
//        {
//            full_name = first_name + " with unknown last name";
//            return full_name;
//        }
//        return full_name;
//    }
//private:
//    std::string GetFirstName(int year, std::map<int, std::string>& firstname)
//    {
//        while (firstname.count(year) == 0 && year > 0)
//        {
//            --year;
//        }
//        std::string first = firstname[year];
//        return first;
//    }
//
//    std::string GetLastName(int year, std::map<int, std::string>& lastname)
//    {
//        while (lastname.count(year) == 0 && year > 0)
//        {
//            --year;
//        }
//        std::string last = lastname[year];
//        return last;
//    }
//private:
//    std::map<int, std::string> first_names;
//    std::map<int, std::string> last_names;
//};
//-------------------------------------------------------------------------------------------------
void test_incognito()
{
    Person person_test;
    person_test.ChangeFirstName(1965, "test_first_name1");
    person_test.ChangeLastName(1967, "test_last_name1");
    assert_equal(person_test.GetFullName(1900), "Incognito", "test_1_incog");
}
//-------------------------------------------------------------------------------------------------
void test_unknown_first_name()
{
    Person person_test;
    person_test.ChangeLastName(1900, "test_last_name1");
    person_test.ChangeFirstName(1905, "test_first_name1");
    assert_equal(person_test.GetFullName(1903), "test_last_name1 with unknown first name", "test_1_unknown_fn");
}
//-------------------------------------------------------------------------------------------------
void test_change_first_name()
{
    Person person_test;
    person_test.ChangeFirstName(1900, "test_first_name1");
    person_test.ChangeFirstName(1902, "test_first_name2");

    assert_equal(person_test.GetFullName(1899),"Incognito", "test_1");
    assert_equal(person_test.GetFullName(1900),"test_first_name1 with unknown last name", "test_1_first_name");
    assert_equal(person_test.GetFullName(1901),"test_first_name1 with unknown last name", "test_1_first_name");
    assert_equal(person_test.GetFullName(1902),"test_first_name2 with unknown last name", "test_1_first_name");
}
//-------------------------------------------------------------------------------------------------
void test_unknown_last_name()
{
    Person person_test;
    person_test.ChangeFirstName(1900, "test_first_name1");
    person_test.ChangeLastName(1905, "test_last_name1");
    assert_equal(person_test.GetFullName(1903), "test_first_name1 with unknown last name", "test_1_unknown_fn");
}
//-------------------------------------------------------------------------------------------------
void test_change_last_name()
{
    Person person_test;
    person_test.ChangeLastName(1900, "test_last_name1");
    person_test.ChangeLastName(1902, "test_last_name2");

    assert_equal(person_test.GetFullName(1899), "Incognito", "test_1");
    assert_equal(person_test.GetFullName(1900), "test_last_name1 with unknown first name", "test_1_last_name");
    assert_equal(person_test.GetFullName(1901), "test_last_name1 with unknown first name", "test_2_last_name");
    assert_equal(person_test.GetFullName(1902), "test_last_name2 with unknown first name", "test_3_last_name");
}
//-------------------------------------------------------------------------------------------------
void test_both_name()
{
    Person person_test;
    person_test.ChangeFirstName(1900, "test_first_name1");
    person_test.ChangeLastName(1902, "test_last_name1");

    assert_equal(person_test.GetFullName(1903), "test_first_name1 test_last_name1", "test_1_both");
}
//-------------------------------------------------------------------------------------------------
void test_change_both_name()
{
    Person person_test;
    person_test.ChangeFirstName(1900, "test_first_name1");
    person_test.ChangeLastName(1902, "test_last_name1");
    person_test.ChangeFirstName(1904, "test_first_name2");
    person_test.ChangeLastName(1905, "test_last_name2");

    assert_equal(person_test.GetFullName(1906), "test_first_name2 test_last_name2", "test_1_both");
}
//-------------------------------------------------------------------------------------------------
void save_first_name()
{
    Person person_test;
    person_test.ChangeFirstName(1900, "test_first_name1");
    person_test.ChangeLastName(1902, "test_last_name1");
    person_test.ChangeFirstName(1905, "test_first_name2");

    assert_equal(person_test.GetFullName(1903), "test_first_name1 test_last_name1", "test_1_save");
}
//-------------------------------------------------------------------------------------------------
void save_last_name()
{
    Person person_test;
    person_test.ChangeLastName(1900, "test_last_name1");
    person_test.ChangeFirstName(1902, "test_first_name1");
    person_test.ChangeLastName(1905, "test_last_name2");

    assert_equal(person_test.GetFullName(1903), "test_first_name1 test_last_name1", "test_1_save");
}
//-------------------------------------------------------------------------------------------------
int main() 
{
    test_runner runner;
    runner.run_test(test_incognito, "test_incognito");
    runner.run_test(test_unknown_first_name, "test_unknown_first_name");
    runner.run_test(test_change_first_name, "test_change_first_name");
    runner.run_test(test_unknown_last_name, "test_unknown_last_name");
    runner.run_test(test_change_last_name, "test_change_last_name");
    runner.run_test(test_both_name, "test_both_name");
    runner.run_test(test_change_both_name, "test_change_both_name");
    runner.run_test(save_first_name, "save_first_name");
    runner.run_test(save_last_name, "save_last_name");
    
    //Person person;
    //person.ChangeFirstName(1965, "Polina");
    //person.ChangeLastName(1967, "Sergeeva");
    //for (int year : {1900, 1965, 1990})
    //{
    //    std::cout << person.GetFullName(year) << std::endl;
    //}

    //person.ChangeFirstName(1970, "Appolinaria");
    //for (int year : {1969, 1970})
    //{
    //    std::cout << person.GetFullName(year) << std::endl;
    //}

    //person.ChangeLastName(1968, "Volkova");
    //for (int year : {1969, 1970})
    //{
    //    std::cout << person.GetFullName(year) << std::endl;
    //}
    return 0;
}
//-------------------------------------------------------------------------------------------------