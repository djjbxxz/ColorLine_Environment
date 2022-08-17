#include "Base.h"
#include <iostream>

#ifdef _PRINT

void Game_map::print()const
{
	std::cout << std::endl;

	//next_three
	std::cout << "      ";
	for (auto&& point : coming_chess)
		std::cout << int(point) << " ";


	for (size_t i = 0; i < _data.size(); i++)
	{
		if (i % BOARD_SIZE == 0)
			std::cout << std::endl;
		std::cout << _data[i].print() << " ";
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