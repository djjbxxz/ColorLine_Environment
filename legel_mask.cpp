#include "legel_mask.h"

using myfunc::is_inlist;



std::vector<Point> Legal_mask::grow_to_max(const Point& startpoint, bool_map& scaned_map)
{
	std::vector<Point>result;
	result.push_back(startpoint);
	scaned_map.set(startpoint, true);
	FOR_RANGE(i,result.size())
	{
		auto& point = result[i];
		auto temp = game_map->get_surround_by_filter(point, [&](const Point& new_point)
			{return (!new_point.outofrange()) &&
			(game_map->get(point) == game_map->get(new_point)) &&
			(scaned_map.get(new_point) == false);
			});
		//if (!temp.empty())
		for (auto&& point : temp)
		{
			result.push_back(point);
			scaned_map.set(point, true);
		}
	}
	return result;
};

void Legal_mask::GetEmptySet()
{
	bool_map scaned_map;
	FOR_RANGE(i,scaned_map._data.size())
	{
		auto point = Point(i);
		if ((scaned_map.get(point) == false) && (game_map->get(point) == Color::empty))
			emptyset.push_back(grow_to_max(point, scaned_map));
	}

}

void Legal_mask::go()
{
	mask.reserve(POTENTIAL_MOVE_NUM);
	GetEmptySet();
	GetBeginSet();
	MakeResult();
}


void Legal_mask::GetBeginSet()
{
	for (auto&& i : emptyset)
		startset.push_back(game_map->dilate(i));
}

void Legal_mask::MakeResult()
{
	for (int i = 0; i < startset.size(); i++)
	{
		calculate(startset[i], emptyset[i]);
	}
}

void Legal_mask::calculate(const std::vector<Point>& start, const std::vector<Point>& end)
{
	for (auto&& i : start)
		for (auto&& j : end)
		{
#ifdef _DEBUG
			assert(mask[Move(i, j).to_densed()] == false);
#endif // _DEBUG
			mask[Move(i, j).to_densed()] = true;
		}
}
