#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>

//-------------------------------------------------------------------------------------------------
int main()
{
    size_t size;
    std::cin >> size;
    std::vector<int> permutation(size);

    std::iota(permutation.begin(), permutation.end(), 1);
    std::reverse(permutation.begin(), permutation.end());

    do 
    {
        std::copy(permutation.begin(), permutation.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    } 
    while (std::prev_permutation(permutation.begin(), permutation.end()));
    return 0;
}
//-------------------------------------------------------------------------------------------------