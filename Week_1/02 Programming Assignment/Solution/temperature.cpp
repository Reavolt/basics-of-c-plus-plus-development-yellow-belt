#include <iostream>
#include <vector>

//-------------------------------------------------------------------------------------------------
int main()
{
	unsigned int size = 0;
	std::cin >> size;

	int64_t sum = 0;
	std::vector<int> temperatures(size);
	for (auto & temperature : temperatures)
	{
		std::cin >> temperature;
		sum += temperature;
	}

	int64_t avg = sum / static_cast<int>(size);
	std::vector<int> result;
	for (size_t i = 0; i < size; i++)
	{
		if (temperatures[i] > avg)
		{
			result.push_back(i);
		}
	}

	std::cout << result.size() << std::endl;

	for (const auto result_index : result)
	{
		std::cout << result_index << " ";
	}
	std::cout << std::endl;
	return 0;
}
//-------------------------------------------------------------------------------------------------