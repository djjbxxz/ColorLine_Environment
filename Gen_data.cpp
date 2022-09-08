#include "gen_data.h"
#include "Pathfinding.h"
#include <iostream>
using Pathfinding::A_star;
using myfunc::exclude;
Direction Gen_data::choos_a_direction(const Point& point)
{
	std::vector<Direction> legal_direction;
	for (const auto& _direct : Direction::eight_neighbor)
		if (!_direct.walk(point, lined_num - 1).outofrange())
			legal_direction.push_back(_direct);
	return Random::rand_choice(legal_direction);
}

std::vector<Point> Gen_data::get_destination(Lined_chess& lined)
{
	std::vector<Point>destinations;
	for (auto& point : lined.possible_destinations)
		if (!point.outofrange())
			destinations.emplace_back(point);
	return destinations;
}

Lined_chess Gen_data::get_lined_chess()
{
	Lined_chess lined_chess;
	Point point;
	do
	{
		//随机取点
		point = game_map->pick_a_spot();

		//计算合法终点
		lined_chess = Lined_chess(game_map, point, choos_a_direction(point), lined_num);
	} while (lined_chess.possible_destinations.empty());
	return lined_chess;
}

void Gen_data::fill_empty()
{
	std::vector<Point>exclusion;
	exclusion.insert(exclusion.end(), pattern.lined.begin(), pattern.lined.end());
	exclusion.insert(exclusion.end(), pattern.path.begin(), pattern.path.end());
	if (!pattern.another_destination.outofrange() && !myfunc::is_inlist(pattern.another_destination, pattern.path))
		exclusion.push_back(pattern.another_destination);
#ifdef _DEBUG
	assert(myfunc::is_unique(exclusion));
#endif // _DEBUG

	auto _empty = exclude(game_map->_empty, exclusion);
	int num_to_fill = BOARD_SIZE * BOARD_SIZE * fill_ratio - lined_num - 1;
	num_to_fill = num_to_fill > 0 ? num_to_fill : 0;
	num_to_fill = num_to_fill > _empty.size() ? _empty.size() : num_to_fill;
	for (size_t i = 0; i < num_to_fill; i++)
	{
		auto index = Random::randint(_empty.size());
		pattern.other.push_back(*_empty[index]);
		_empty.erase(_empty.begin() + index);
	}

}

void Gen_data::set_rand_coming_chess()
{
	std::array<Color, COMING_CHESS_NUM>temp;
	FOR_RANGE(i, COMING_CHESS_NUM)
		temp[i] = Color::rand_color();
	game_map->set_coming_chess(temp);
}


void Gen_data::go()
{
	do
	{
		reset();
		auto lined = get_lined_chess();
		pattern.set(lined);
		auto path = A_star(lined).get_path();
		pattern.set_path(path);
		fill_empty();
		paint();
	} while (!validate());
	set_rand_coming_chess();
}

void Gen_data::paint()
{

}

#ifdef _PRINT
void Gen_data::print()
{
	pattern.print();
	game_map->print();
}
#endif // DEBUG
bool Gen_data::validate()const
{
	return Game_rule::Scan_all(*game_map).empty();
}

void Board_pattern::set(Lined_chess& _lined)
{

}

void Board_pattern::set_path(const std::vector<Point>& _path)
{
	path = _path;
}
#ifdef _PRINT
void Board_pattern::print()const
{

}
#endif // DEBUG


