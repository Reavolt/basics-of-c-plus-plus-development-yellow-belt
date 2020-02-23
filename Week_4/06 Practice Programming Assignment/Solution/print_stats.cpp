//#include "test_runner.h"
#include <vector>
#include <iostream>
#include <algorithm>

//-------------------------------------------------------------------------------------------------
//enum class Gender 
//{
//    FEMALE,
//    MALE
//};
//-------------------------------------------------------------------------------------------------
//struct Person 
//{
//    int age; 
//    Gender gender;
//    bool is_employed; 
//};
//-------------------------------------------------------------------------------------------------
//template <typename InputIt>
//int ComputeMedianAge(InputIt range_begin, InputIt range_end) 
//{
//    if (range_begin == range_end)
//    {
//        return 0;
//    }
//
//    std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
//    auto middle = std::begin(range_copy) + range_copy.size() / 2;
//    
//    std::nth_element( std::begin(range_copy), middle, std::end(range_copy),
//        [](const Person& lhs, const Person& rhs) 
//        {
//            return lhs.age < rhs.age;
//        });
//    return middle->age;
//}
//-------------------------------------------------------------------------------------------------
void PrintStats(std::vector<Person> persons)
{
   std::cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << std::endl;;
   
   std::cout << "Median age for females = " << 
   ComputeMedianAge(persons.begin(), std::partition(persons.begin(), persons.end(),
       [](const Person& pers)
       {
           return pers.gender == Gender::FEMALE; 
       })) << std::endl;

   std::cout << "Median age for males = " << 
   ComputeMedianAge(persons.begin(), std::partition(persons.begin(), persons.end(),
       [](const Person& pers)
       {
           return pers.gender == Gender::MALE; 
       })) << std::endl;

   std::cout << "Median age for employed females = " << 
   ComputeMedianAge(persons.begin(), std::partition(persons.begin(), persons.end(),
       [](const Person& pers)
       {
           return pers.gender == Gender::FEMALE && pers.is_employed == true;
       })) << std::endl;

   std::cout << "Median age for unemployed females = " << 
   ComputeMedianAge(persons.begin(), std::partition(persons.begin(), persons.end(),
       [](const Person& pers)
       {
           return pers.gender == Gender::FEMALE && pers.is_employed == false;
       })) << std::endl;

   std::cout << "Median age for employed males = " << 
   ComputeMedianAge(persons.begin(), std::partition(persons.begin(), persons.end(),
       [](const Person& pers)
       {
           return pers.gender == Gender::MALE && pers.is_employed == true;
       })) << std::endl;

   std::cout << "Median age for unemployed males = " << 
   ComputeMedianAge(persons.begin(), std::partition(persons.begin(), persons.end(),
       [](const Person& pers)
       {
           return pers.gender == Gender::MALE && pers.is_employed == false;
       })) << std::endl;
}
//-------------------------------------------------------------------------------------------------
//int main()
//{
//    std::vector<Person> persons = 
//    {
//       {31, Gender::MALE, false},
//       {40, Gender::FEMALE, true},
//       {24, Gender::MALE, true},
//       {20, Gender::FEMALE, true},
//       {80, Gender::FEMALE, false},
//       {78, Gender::MALE, false},
//       {10, Gender::FEMALE, false},
//       {55, Gender::MALE, true},
//    };
//    PrintStats(persons);
//    return 0;
//}
//-------------------------------------------------------------------------------------------------