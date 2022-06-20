#include "head.h"
#include <algorithm>
#ifdef DEBUG
#include <assert.h>
#endif // DEBUG
void Gen_data::random_lay_chess(game_map map, char lay_num)
{
	//auto index = random->rand_choice(map.empty.size());
}

void game_map::lay_chess(const Point& point,color _color)
{
#ifdef DEBUG
	assert(inspect(point) == empty);
#endif // DEBUG
	data[point.index()] = _color;
	erase_from_empty(point);
}

void game_map::lay_chess(int index, color _color)
{
	lay_chess(_empty[index], _color);
}

color game_map::inspect(int index) const
{
	return color(data[index]);
}

color game_map::inspect(const Point& point) const
{
	return color(data[point.index()]);
}

void game_map::erase_from_empty(const Point& point)
{
	for (auto i = _empty.begin(); i != _empty.end(); i++)
	{
		if (point == *i)
		{
			_empty.erase(i);
			break;
		}
#ifdef DEBUG
		assert(i < _empty.end());
#endif // DEBUG

	}
}

void game_map::erase_from_empty(int index)
{
	_empty.erase(_empty.begin()+index);
	auto point = Point{ index };
	erase_from_empty(point);
}

void game_map::print()
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (i / BOARD_SIZE > 0)
			std::cout << std::endl;
		std::cout << int(data[i]);
	}
	for (const auto& point : data)
	{
		std::cout << int(point);
	}
}