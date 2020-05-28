#include <iostream>

int main()
{
	uint64_t N{ 0 }, R{ 0 }, sum{ 0 };
	std::cin >> N >> R;

	for (uint64_t i = 0; i < N; ++i)
	{
		uint64_t W{ 0 }, D{ 0 }, H{ 0 };
		std::cin >> W >> D >> H;
		sum += (W * D * H);
	}

	std::cout << sum * R;

	return 0;
}