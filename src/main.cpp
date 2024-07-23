#include <iostream>

#include "MinHasher.hpp"

int main()
{
	using dtype = int;

	MinHasher<dtype>::datalist_t setList{
		{1, 0, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 1, 1},
		{1, 0, 1, 1, 0}
	};

	MinHasher<dtype>::hashfunclist_t hashFunctions{
		[](dtype x) { return (x + 1) % 5; },
		[](dtype x) { return (3 * x + 1) % 5; },
		[](dtype x) { return (2 * x + 4) % 5; },
		[](dtype x) { return (3 * x - 1) % 5; }
	};

	MinHasher<dtype> minHasher{ setList, hashFunctions };

	auto sigList = minHasher.GetSignatureList();

	for (const auto& signature : sigList)
	{
		for (const auto& val : signature)
		{
			std::cout << val << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}