#ifndef _EXPORT



#include <iostream>
#include "gen_data.h"
#include "Export.h"

using namespace export_bind;
int main()
{
#ifdef _DEBUG
	std::cout << "DEBUG\n";
#endif



#ifdef _DEBUG
	using namespace std;
	int lined_num = 4;
	float fill_ratio = 1;
	int times = 1;

	auto game_map = Game_map();
	auto a = Gen_data(lined_num, fill_ratio, &game_map);
	a.go();
	game_map.print();
	auto mask = Legal_mask(game_map).get_result();
	auto &move = a.pattern._move;
	move.print();

	auto reward = Game_rule(game_map, move).rule();
	game_map.print();
	std::cout << "reward: " << reward<<std::endl;
#endif

#ifdef _PERFTEST
	int lined_num = 3;
	float fill_ratio = 0.99;
	int times = 100000;

	generate_data(times, lined_num, fill_ratio);
	std::vector< Data_pack*> result;
	result.reserve(times);
	FOR_RANGE(i, times)
		result.push_back(get_result(i));

#endif

}
#endif

