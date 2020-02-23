#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

//-------------------------------------------------------------------------------------------------
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (std::distance(range_begin, range_end) < 2)
    {
        return;
    }
    else
    {
        std::vector<typename RandomIt::value_type> elements(range_begin, range_end);

        auto itr_part_1 = elements.begin() + elements.size() / 2;

        MergeSort(elements.begin(), itr_part_1);
        MergeSort(itr_part_1, elements.end());

        std::merge(elements.begin(), itr_part_1, itr_part_1, elements.end(), range_begin);
    }
}
//-------------------------------------------------------------------------------------------------
int main()
{
    std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) 
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}
//-------------------------------------------------------------------------------------------------