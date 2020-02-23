#include <iostream>
#include <cstdint>

//----------------------------------------------------------------------------------------------------
int main()
{
	int  quantity = 0;
	std::cin >> quantity;

	int  density = 0;
	std::cin >> density;

	uint64_t weight = 0;

	for (int i = 0; i < quantity; ++i)
	{
		int  width = 0;
		std::cin >> width;

		int  height = 0;
		std::cin >> height;

		int  length = 0;
		std::cin >> length;

		weight += static_cast<uint64_t>(width) * height * length;
	}
	weight *= density;
	std::cout << weight << std::endl;

	return 0;
}
//----------------------------------------------------------------------------------------------------