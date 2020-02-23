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

        auto itr_part_1 = elements.begin() + elements.size() / 3;
        auto itr_part_2 = itr_part_1 + elements.size() / 3;

        MergeSort(elements.begin(), itr_part_1);
        MergeSort(itr_part_1, itr_part_2);
        MergeSort(itr_part_2, elements.end());

        std::vector<typename RandomIt::value_type> temp;

        std::merge(elements.begin(), itr_part_1, itr_part_1, itr_part_2, std::back_inserter(temp));
        std::merge(temp.begin(), temp.end(), itr_part_2, elements.end(), range_begin);
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