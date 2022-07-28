#pragma once

#include <vector>
#include <random>


#ifdef _DEBUG
#include <assert.h>
#endif // DEBUG

#define FOR_RANGE(PLACEHOLDER,NUM) for(int PLACEHOLDER=0;PLACEHOLDER<NUM;PLACEHOLDER++)

namespace myfunc
{
	template <typename T>
	std::vector<typename std::vector<T>::iterator>
		exclude(std::vector<T>& items, const std::vector<T>& exclusion)
	{
		std::vector<typename std::vector<T>::const_iterator> ptr_items;
		std::vector<typename std::vector<T>::const_iterator> ptr_exclusion;
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

	template <typename T>
	std::vector<typename std::vector<T>::const_iterator>
		exclude(const std::vector<T>& items, const std::vector<T>& exclusion)
	{
		std::vector<typename std::vector<T>::const_iterator> ptr_items;
		std::vector<typename std::vector<T>::const_iterator> ptr_exclusion;
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

	template <typename T>
	bool is_unique(const std::vector<T>& items)
	{
		for (auto i = items.begin(); i != items.end(); i++)
			for (auto j = i + 1; j != items.end(); j++)
				if (*i == *j)
					return false;
		return true;
	}

	template <typename T>
	bool is_inlist(const T& a, const std::vector<T>& list)
	{
		for (const auto& item : list)
			if (a == item)
				return true;
		return false;
	}

	template <typename T>
	bool operator==(const std::vector<T>& a, const std::vector<T>& b)
	{
		if (a.size() != b.size())
			return false;
		std::vector<typename std::vector<T>::const_iterator> ptr_a;
		std::vector<typename std::vector<T>::const_iterator> ptr_b;
		ptr_a.reserve(a.size());
		ptr_b.reserve(b.size());
		for (auto i = a.begin(); i != a.end(); i++)
			ptr_a.emplace_back(i);
		for (auto i = b.begin(); i != b.end(); i++)
			ptr_b.emplace_back(i);
		for (auto i = ptr_a.begin(); i != ptr_a.end();)
		{
			if (my_remove(*i, ptr_b,
				[](const typename std::vector<T>::const_iterator& a, typename std::vector<T>::const_iterator& b)
				->bool {return *a == *b; }))
				i = ptr_a.erase(i);
			else
				return false;
		}
		return ptr_a.empty() && ptr_b.empty();
	}

	//remove only once if repeat
	template <typename T, typename FUNC>
	bool my_remove(const T& item, std::vector<T>& list, FUNC condition)
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

	//return first element found that meet the condition
	template <typename T, typename FUNC>
	T& find_first(std::vector<T>list,FUNC condition)
	{
		for (auto && item:list)
			if (condition(item))
				return item;
	}

	class Random;
};

class myfunc::Random
{
public:

	Random() = delete;

	template <typename T>
	static T& rand_choice(std::vector<T>& items)
	{
#ifdef _DEBUG
		assert(!items.empty());
#endif // DEBUG

		std::uniform_int_distribution<int> dist(0, items.size() - 1);
		return items[dist(mt)];
	}

	template <typename T>
	static const T& rand_choice(const std::vector<T>& items)
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
		return (_random(mt)) % max;
	}

private:
	static std::mt19937 mt;
	static std::uniform_int_distribution<int> _random;
};
