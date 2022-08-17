#ifndef _EXPORT



#include <iostream>
#include "gen_data.h"
#include "Export.h"

using namespace export_bind;
using namespace myfunc;
int main(int argc, char* argv[])
{
#ifdef _DEBUG
	std::cout << "DEBUG\n";
#endif


#ifdef _DEBUG
	using namespace std;
	//int lined_num = 4;
	//float fill_ratio = 0.5;
	//int lined_num = atof(argv[1]);
	//float fill_ratio = atof(argv[2]);
	int lined_num = 1;
	float fill_ratio = 0.1;
	int times = 1;

	int reward = 0;

	auto game_map = Game_map();
	auto a = Gen_data(lined_num, fill_ratio, &game_map);
	a.go();
	game_map.print();
	int score = 0;
	int length = 0;
	do
	{
		length++;
		auto mask = Legal_mask(game_map).get_result();
		auto move = Move(find_first_index(mask, [](int& c) {return c == 1; }));
		move.print();

		reward = Game_rule(game_map, move).rule();
		if (reward>0)
			score += reward;
		game_map.print();
		std::cout << "reward: " << reward << std::endl;
	} while (reward != -1);
	std::cout << "score: " << score << std::endl;
	std::cout << "step: " << length<< std::endl;


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

