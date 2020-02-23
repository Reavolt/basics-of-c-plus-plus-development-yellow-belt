#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//-------------------------------------------------------------------------------------------------
template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
    auto itr = std::equal_range(range_begin, range_end, std::string(1, prefix),
        [](const std::string& x, const std::string& y)
        { 
            return x[0] < y[0];
        });
    return std::make_pair(itr.first, itr.second);
}
//--------------------------------------------------------------------------------------------------
int main()
{
    const std::vector<std::string> sorted_strings = { "moscow", "murmansk", "vologda" };

    const auto m_result = FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'm');
    
    for (auto it = m_result.first; it != m_result.second; ++it) 
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto p_result = FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'p');
    std::cout << (p_result.first - std::begin(sorted_strings)) << " " 
    << (p_result.second - std::begin(sorted_strings)) << std::endl;

    const auto z_result = FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'z');
    std::cout << (z_result.first - std::begin(sorted_strings)) << " " 
    << (z_result.second - begin(sorted_strings)) << std::endl;

	return 0;
}
//-------------------------------------------------------------------------------------------------