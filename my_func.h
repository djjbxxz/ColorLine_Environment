#pragma once

#include <vector>
#include <random>
#include <concepts>
#include <type_traits>
#include<array>
#ifdef _DEBUG
#include <assert.h>
#endif // DEBUG

#define FOR_RANGE(PLACEHOLDER,NUM) for(int PLACEHOLDER=0;PLACEHOLDER<NUM;PLACEHOLDER++)

namespace mytrait
{
	template <typename T>
	struct is_std_array : std::false_type {};

	template < typename T, std::size_t N>
	struct is_std_array<std::array<T, N> > : std::true_type { };

	template <typename T>
	struct is_std_vector : std::false_type {};

	template < typename T>
	struct is_std_vector<std::vector<T> > : std::true_type { };

}

namespace myconcept
{
	template<typename T>
	concept IsVectorOrArray = mytrait::is_std_array<T>::value || mytrait::is_std_vector<T>::value;

	template<typename T>
	concept NoVectorBool = requires(T vec)
	{
		mytrait::is_std_vector<T>::value && !std::same_as<typename T::value_type, bool>;
	};
}

namespace myfunc
{
	//template <myconcept::IsVectorOrArray ITEM, myconcept::IsVectorOrArray EXCLUSION>
	//std::vector<typename ITEM::iterator>
	//	exclude(ITEM& items, const EXCLUSION& exclusion)
	//{
	//	std::vector<ITEM::const_iterator> ptr_items;
	//	std::vector<EXCLUSION::const_iterator> ptr_exclusion;
	//	ptr_items.reserve(items.size());
	//	ptr_exclusion.reserve(exclusion.size());
	//	for (auto i = items.begin(); i != items.end(); i++)
	//		ptr_items.emplace_back(i);
	//	for (auto i = exclusion.begin(); i != exclusion.end(); i++)
	//		ptr_exclusion.emplace_back(i);
	//	while (true)
	//	{
	//		auto i = ptr_exclusion.begin();
	//		for (auto j = ptr_items.begin(); j != ptr_items.end();)
	//			if (**i == **j)
	//			{
	//				i = ptr_exclusion.erase(i);
	//				j = ptr_items.erase(j);
	//				break;
	//			}
	//			else
	//				j++;
	//		if (ptr_exclusion.empty())
	//			break;
	//	}
	//	return ptr_items;
	//}

	template <myconcept::IsVectorOrArray ITEM, myconcept::IsVectorOrArray EXCLUSION>
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

	template <myconcept::IsVectorOrArray Arr>
	bool is_unique(const Arr& items)
	{
		for (auto i = items.begin(); i != items.end(); i++)
			for (auto j = i + 1; j != items.end(); j++)
				if (*i == *j)
					return false;
		return true;
	}

	template <typename T, myconcept::IsVectorOrArray Arr>
		requires(std::same_as<typename Arr::value_type, T>)
	bool is_inlist(const T& a, const Arr& list)
	{
		for (const auto& item : list)
			if (a == item)
				return true;
		return false;
	}

	template <myconcept::IsVectorOrArray A, myconcept::IsVectorOrArray B>
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
		requires(mytrait::is_std_vector<Arr>::value&& std::same_as<typename Arr::value_type, T>)
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

	//return first element found that meet the condition
	//template <myconcept::IsVectorOrArray Arr, typename FUNC>
	//Arr::value_type& find_first(Arr list, FUNC condition)
	//{
	//	for (auto&& item : list)
	//		if (condition(item))
	//			return item;
	//}

	//template <myconcept::IsVectorOrArray Arr, typename FUNC>
	//size_t find_first_index(Arr list, FUNC condition)
	//{
	//	for(size_t i = 0;i<list.size();i++)
	//		if (condition(list[i]))
	//			return i;
	//}

	class Random;

	template<typename T>
		requires (mytrait::is_std_array<T>::value)
	std::vector<typename T::value_type>from_std_array(const T& arr)
	{
		return std::vector(arr.begin(), arr.end());
	}
};

class myfunc::Random
{
public:

	Random() = delete;

	template <myconcept::IsVectorOrArray Arr>
		requires myconcept::NoVectorBool<Arr>
	static Arr::value_type& rand_choice(Arr& items)
	{
#ifdef _DEBUG
		assert(!items.empty());
#endif // DEBUG

		std::uniform_int_distribution<int> dist(0, items.size() - 1);
		return items[dist(mt)];
	}

	template <myconcept::IsVectorOrArray Arr>
		requires myconcept::NoVectorBool<Arr>
	static const Arr::value_type& rand_choice(const Arr& items)
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
