#include <iostream>
#include <map>
#include <vector>

//-------------------------------------------------------------------------------------------------
template<typename T>
T Sqr(T value);
template<typename T>
std::vector<T> Sqr(const std::vector<T>& vectr);
template<typename key, typename value>
std::map<key, value> Sqr(const std::map<key, value>& map_arg);
template<typename first, typename second>
std::pair<first, second> Sqr(const std::pair<first, second>& pair_arg);
//-------------------------------------------------------------------------------------------------
int main()
{
    // Пример вызова функции
    std::vector<int> v = { 1, 2, 3 };
    
    std::cout << "vector:";
    
    for (int x : Sqr(v)) 
    {
        std::cout << ' ' << x;
    }
    std::cout << std::endl;

    std::map<int, std::pair<int, int>> map_of_pairs = 
    {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    std::cout << "map of pairs:" << std::endl;

    for (const auto& x : Sqr(map_of_pairs)) 
    {
        std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T Sqr(T value) 
{
    return value * value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::vector<T> Sqr(const std::vector<T>& vectr)
{
    std::vector<T> tmp;

    for (const T & item : vectr)
    {
        tmp.push_back(Sqr(item));
    }
    return tmp;
}
//-------------------------------------------------------------------------------------------------
template<typename key, typename value>
std::map<key, value> Sqr(const std::map<key, value>& map_arg)
{
    std::map<key, value> temp;
    for (auto & item : map_arg)
    {
        temp[item.first] = Sqr(item.second);
    }
    return temp;
}
//-------------------------------------------------------------------------------------------------
template<typename first, typename second>
std::pair<first, second> Sqr(const std::pair<first, second>& pair_arg)
{
    return {Sqr(pair_arg.first), Sqr(pair_arg.second)};
}
//-------------------------------------------------------------------------------------------------