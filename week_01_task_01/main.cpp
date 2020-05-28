#include <iostream>
#include <vector>

int main()
{
	size_t cntValues{ 0 };
	std::vector<int64_t> vecValues;

	std::cin >> cntValues;
	vecValues.reserve(cntValues);

	int64_t sum{ 0 };
	for (size_t i = 0; i < cntValues; ++i)
	{
		int64_t val{ 0 };
		std::cin >> val;
		vecValues.push_back(val);
		sum += val;
	}

	int64_t avg = sum / static_cast<int64_t>(cntValues);

	int cntMore{ 0 };
	for (auto&& val : vecValues)
	{
		if (val > avg)
			cntMore++;
	}

	std::cout << cntMore << std::endl;
	for (size_t i = 0; i < vecValues.size(); ++i)
	{
		if (vecValues[i] > avg)
			std::cout << i << " ";
	}
		
	return 0;
}