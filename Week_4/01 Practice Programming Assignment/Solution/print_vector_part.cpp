#include <algorithm>
#include <iostream>
#include <vector>

//-------------------------------------------------------------------------------------------------
void PrintVectorPart(const std::vector<int>& numbers)
{
    auto itr = std::find_if(numbers.begin(), numbers.end(), [](const int& x) { return x < 0; });
    while (itr != numbers.begin())
    {
        itr--;
        std::cout << *itr << " ";
    }
}
//-------------------------------------------------------------------------------------------------
int main() 
{
    PrintVectorPart({ 6, 1, 8, -5, 4 });
    std::cout << std::endl;
    PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
    std::cout << std::endl;
    PrintVectorPart({ 6, 1, 8, 5, 4 });
    std::cout << std::endl;

    return 0;
}
//-------------------------------------------------------------------------------------------------