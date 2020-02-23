#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <string>

//-------------------------------------------------------------------------------------------------
template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border)
{
    auto itr = std::find_if(elements.begin(), elements.end(), [border](const T& x) { return x > border; });

    std::vector<T> temp;
    for (auto i = itr; i != elements.end(); i++)
    {
        temp.push_back(*i);
    }
    return temp;
}
//-------------------------------------------------------------------------------------------------
int main() 
{
    for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) 
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::string to_find = "Python";
    std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;

    return 0;
}
//-------------------------------------------------------------------------------------------------