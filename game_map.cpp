#include "Base.h"
#include <iostream>

void Game_map::set(const Point& point, Color _color)
{
#ifdef _DEBUG
	assert(get(point) == Color::empty);
#endif // DEBUG
	data[point.index()] = _color;
}

void Game_map::set(std::vector<Point>& points, Color _color)
{
	for (const auto& point : points)
	{
#ifdef _DEBUG
		assert(get(point) == Color::empty);
#endif // DEBUG
		data[point.index()] = _color;
	}
}

const Color& Game_map::operator[](int index)const
{//get data in 1D index
#ifdef _DEBUG
	assert(index < BOARD_SIZE* BOARD_SIZE&& index >= 0);
#endif // DEBUG
	return data[index];
}

const Color& Game_map::get(int row, int colomn) const
{//get data in 2D index
	return (*this)[row * BOARD_SIZE + colomn];
}

const Color& Game_map::get(const Point& point) const
{//get data in 2D index
	return (*this)[point.x * BOARD_SIZE + point.y];
}
#ifdef _DEBUG

void Game_map::print()
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (i % BOARD_SIZE == 0)
			std::cout << std::endl;
		std::cout << data[i].print() << " ";
	}
	std::cout << std::endl << std::endl;
}
#endif // _DEBUG

const Point& Game_map::pick_a_spot(const std::vector<Point>& exclusion)const
{//randomly pick a spot from empty spots, skip those from exclusion

	auto new_empty = myfunc::exclude(_empty, exclusion);
	
	return *Random::rand_choice(new_empty);
}


const Point& Game_map::pick_a_spot()const
{
	return Random::rand_choice(_empty);
}