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

const std::array <Direction, 8> Direction::eight_neighbor{
	_direction::north,
		_direction::northeast,
		_direction::east,
		_direction::southeast,
		_direction::south,
		_direction::southwest,
		_direction::west,
		_direction::northwest
};

const std::array <Direction, 4> Direction::four_neighbor ={
	_direction::north,
		_direction::east,
		_direction::south,
		_direction::west
};

const std::array <Direction, 4> Direction::scan_direction ={
	_direction::north,
		_direction::northeast,
		_direction::east,
		_direction::southeast
};

Color Color::rand_color_except(std::vector<Color>& exclusion)
{
	auto temp = myfunc::from_std_array(all_color);
	std::remove_if(temp.begin(), temp.end(),
		[&](Color& point) ->bool {
			return !(std::find(exclusion.begin(), exclusion.end(), point) == exclusion.end());
		});
	return Random::rand_choice(temp);
}

Color Color::rand_color_except(Color _color)
{
	auto temp = myfunc::from_std_array(all_color);
	temp.erase(std::find(temp.begin(), temp.end(), _color));
	return Random::rand_choice(temp);

}

Color Color::rand_color()
{
	return Random::rand_choice(all_color);
}

Color Color::rand_statu_except(Color _color)
{
	auto temp = myfunc::from_std_array(all_statu);
	temp.erase(std::find(temp.begin(), temp.end(), _color));
	return Random::rand_choice(temp);
}

const std::array<Color, COLOR_NUM> Color::all_color = Color::all_color_init();

const std::array<Color, COLOR_NUM + 1> Color::all_statu = Color::all_statu_init();

const Color Color::empty = Color(_color::empty);

std::array<Point, CHESS_NUM> Game_map::_empty_init()
{
	std::array<Point, CHESS_NUM>__empty;
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
		__empty[i] = i;
	return __empty;
}

const std::array<Point, CHESS_NUM> Game_map::_empty = Game_map::_empty_init();

bool Game_map::is_all_empty()const {
	for (auto&& color : _data)
		if (color != Color::empty)
			return false;
	return true;
}

std::array<Color, COLOR_NUM>Color::all_color_init()
{
	std::array<Color, 7> all_color = {
	_color::green,
	_color::red,
	_color::dark_blue,
	_color::yellow,
	_color::light_blue,
	_color::purple,
	_color::brown
	};
	std::array<Color, COLOR_NUM>temp;
	FOR_RANGE(i, COLOR_NUM)
		temp[i] = all_color[i];
	return temp;
}

std::array<Color, COLOR_NUM + 1>Color::all_statu_init()
{
	std::array<Color, COLOR_NUM + 1>temp;
	temp[0] = Color::empty;
	FOR_RANGE(i, COLOR_NUM)
		temp[i + 1] = all_color[i];
	return temp;
}