#pragma once

#include <vector>
#include <random>
#include<array>
#ifdef _DEBUG
#include <assert.h>
#endif // DEBUG

#define FOR_RANGE(PLACEHOLDER,NUM) for(int PLACEHOLDER=0;PLACEHOLDER<NUM;PLACEHOLDER++)


namespace myfunc
{
	template <typename ITEM, typename EXCLUSION>
	std::vector<typename ITEM::const_iterator>
		exclude(const ITEM& items, const EXCLUSION& exclusion)
	{
		std::vector<typename ITEM::const_iterator> ptr_items;
		std::vector<typename EXCLUSION::const_iterator> ptr_exclusion;
		ptr_items.reserve(items.size());
		ptr_exclusion.reserve(exclusion.size());
		for (auto i = items.begin(); i != items.end(); i++)
			ptr_items.emplace_back(i);
		for (auto i = exclusion.begin(); i != exclusion.end(); i++)
			ptr_exclusion.emplace_back(i);
		while (true)
		{
			auto i = ptr_exclusion.begin();
			for (auto j = ptr_items.begin(); j != ptr_items.end();)
				if (**i == **j)
				{
					i = ptr_exclusion.erase(i);
					j = ptr_items.erase(j);
					break;
				}
				else
					j++;
			if (ptr_exclusion.empty())
				break;
		}
		return ptr_items;
	}

	template <typename Arr>
	bool is_unique(const Arr& items)
	{
		for (auto i = items.begin(); i != items.end(); i++)
			for (auto j = i + 1; j != items.end(); j++)
				if (*i == *j)
					return false;
		return true;
	}

	template <typename T, typename Arr>
	bool is_inlist(const T& a, const Arr& list)
	{
		for (const auto& item : list)
			if (a == item)
				return true;
		return false;
	}

	template <typename A, typename B>
	bool operator==(const A& a, const B& b)
	{
		if (a.size() != b.size())
			return false;
		std::vector<typename A::const_iterator> ptr_a;
		std::vector<typename B::const_iterator> ptr_b;
		ptr_a.reserve(a.size());
		ptr_b.reserve(b.size());
		for (auto i = a.begin(); i != a.end(); i++)
			ptr_a.emplace_back(i);
		for (auto i = b.begin(); i != b.end(); i++)
			ptr_b.emplace_back(i);
		for (auto i = ptr_a.begin(); i != ptr_a.end();)
		{
			if (remove(*i, ptr_b,
				[](const typename A::const_iterator& a, typename B::const_iterator& b)
				->bool {return *a == *b; }))
				i = ptr_a.erase(i);
			else
				return false;
		}
		return ptr_a.empty() && ptr_b.empty();
	}

	//remove only once if repeat
	template <typename T, typename FUNC, typename Arr>
	bool remove(const T& item, Arr& list, FUNC condition)
	{
		for (auto i = list.begin(); i != list.end();)
			if (condition(item, *i))
			{
				list.erase(i);
				return true;
			}
			else
				i++;
		return false;
	}

	class Random;

	template<typename T>
	std::vector<typename T::value_type>from_std_array(const T& arr)
	{
		return std::vector<typename T::value_type>(arr.begin(), arr.end());
	}
};

class myfunc::Random
{
public:

	Random() = delete;

	template <typename Arr>
	static typename Arr::value_type& rand_choice(Arr& items)
	{
#ifdef _DEBUG
		assert(!items.empty());
#endif // DEBUG

		std::uniform_int_distribution<int> dist(0, items.size() - 1);
		return items[dist(mt)];
	}

	template <typename Arr>
	static const typename Arr::value_type& rand_choice(const Arr& items)
	{
#ifdef _DEBUG
		assert(!items.empty());
#endif // DEBUG

		std::uniform_int_distribution<int> dist(0, items.size() - 1);
		return items[dist(mt)];
	}


	static int randint(int max)
	{//return [0,max) integer
#ifdef _DEBUG
		assert(max > 0 && max <= INT32_MAX);
#endif
		if (max == 0)
			throw "function: randint arg[0] can not be zero!";
		return (_random(mt)) % max;
	}

private:
	static std::mt19937 mt;
	static std::uniform_int_distribution<int> _random;
};
