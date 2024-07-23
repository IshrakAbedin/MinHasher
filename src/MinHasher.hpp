#pragma once

#include <vector>
#include <functional>

#define USE_STD_RANGES

#ifdef USE_STD_RANGES
#include <ranges>
#endif // USE_STD_RANGES

#ifndef USE_STD_RANGES
#include <numeric>
#endif // !USE_STD_RANGES

template<typename T>
class MinHasher
{
public:
	using datalist_t = std::vector<std::vector<T>>;
	using hashfunclist_t = std::vector<std::function<T(T)>>;

#ifndef USE_STD_RANGES
	static constexpr auto MAX_VALUE = std::numeric_limits<T>::max();
#endif // !USE_STD_RANGES


private:
	datalist_t m_CharacteristicsList;
	hashfunclist_t m_HashFunctions;
	size_t m_SetCount;
	size_t m_SetSize;
	size_t m_HashCount;

public:
	MinHasher(const datalist_t& characteristicsList, const hashfunclist_t& hashFunctions)
		: m_CharacteristicsList{ characteristicsList }, m_HashFunctions{ hashFunctions }
	{
		m_SetCount = characteristicsList.size();
		m_SetSize = characteristicsList[0].size();
		m_HashCount = hashFunctions.size();
	}

	datalist_t GetSignatureList() const
	{
		datalist_t signatureList;
		signatureList.reserve(m_SetCount);

#ifdef USE_STD_RANGES
		for (const auto& set : m_CharacteristicsList)
		{
			std::vector<T> row;
			row.reserve(m_HashCount);

			const auto& maskFilter = [&](size_t x) { return set[x]; };

			for (const auto& h : m_HashFunctions)
			{
				row.push_back(
					std::ranges::min(
						std::views::iota(0u)
						| std::views::take(m_SetSize)
						| std::views::filter(maskFilter)
						| std::views::transform(h)
					)
				);
			}

			signatureList.push_back(std::move(row));
		}
#else // !USE_STD_RANGES
		for (size_t i = 0u; i < m_SetCount; i++)
		{
			std::vector<T> row;
			row.reserve(m_HashCount);

			for (size_t j = 0u; j < m_HashCount; j++)
			{
				row.push_back(MAX_VALUE);
			}
			signatureList.push_back(std::move(row));
		}

		for (size_t i = 0u; i < m_SetSize; i++)
		{
			for (size_t j = 0u; j < m_HashCount; j++)
			{
				const auto& h = m_HashFunctions[j];
				const auto hashval = h(i);
				for (size_t s = 0u; s < m_SetCount; s++)
				{
					if (m_CharacteristicsList[s][i])
					{
						signatureList[s][j] = (hashval < signatureList[s][j]) ? hashval : signatureList[s][j];
					}
				}
			}
		}
#endif // USE_STD_RANGES

		return signatureList;
	}
};