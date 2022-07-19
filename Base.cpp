#pragma once
#include "Base.h"


const std::map < Direction::_direction, Point > Direction::direct2point = std::map < Direction::_direction, Point >{
	   {_direction::north,{ -1,0 }},
	   {_direction::northeast,{ -1,1 }},
	   {_direction::east,{ 0,1 }},
	   {_direction::southeast,{1,1}},
	   {_direction::south,{ 1,0 }},
	   {_direction::southwest,{ 1,-1 }},
	   {_direction::west,{ 0,-1 }},
	   {_direction::northwest,{ -1,-1 }}
};

const std::vector<Direction> Direction::eight_direction = std::vector<Direction>{
	{_direction::north},
	{_direction::northeast},
	{_direction::east},
	{_direction::southeast},
	{_direction::south},
	{_direction::southwest},
	{_direction::west},
	{_direction::northwest}
};

const std::vector<Direction> Direction::four_direction = std::vector<Direction>{
	{_direction::north},
	{_direction::east},
	{_direction::south},
	{_direction::west}
};

Color Color::rand_color_except(std::vector<Color>& exclusion)
{
	auto temp = all_color;
	std::remove_if(temp.begin(), temp.end(),
		[&](Color& point) ->bool {
			return !(std::find(exclusion.begin(), exclusion.end(), point) == exclusion.end());
		});
	return Random::rand_choice(temp);
}

Color Color::rand_color_except(Color _color)
{
	auto temp = all_color;
	temp.erase(std::find(temp.begin(), temp.end(), _color));
	return Random::rand_choice(temp);

}

Color Color::rand_color()
{
	return Random::rand_choice(all_color);
}

Color Color::rand_statu_except(Color _color)
{
	auto temp = all_statu;
	temp.erase(std::find(temp.begin(), temp.end(), _color));
	return Random::rand_choice(temp);
}

const std::vector<Color> Color::all_color = std::vector<Color>{
	_color::green,
	_color::red,
	_color::dark_blue,
	_color::yellow,
	_color::light_blue,
	_color::purple,
	_color::brown
};

const std::vector<Color> Color::all_statu = std::vector<Color>{
	_color::empty,
	_color::green,
	_color::red,
	_color::dark_blue,
	_color::yellow,
	_color::light_blue,
	_color::purple,
	_color::brown
};

const Color Color::empty = Color(_color::empty);

std::vector<Point> Game_map::_empty_init()
{
	std::vector<Point>__empty;
	__empty.reserve(BOARD_SIZE * BOARD_SIZE);
	for (int i=0;i<BOARD_SIZE*BOARD_SIZE;i++)
		__empty.emplace_back(i);
	return __empty;
}
//const std::vector<Point> Game_map::_empty = std::vector<Point>{ };
const std::vector<Point> Game_map::_empty = Game_map::_empty_init();

