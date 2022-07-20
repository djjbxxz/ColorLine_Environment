#include "gen_data.h"
#include <iostream>

#include "threadpool.h"


void func(int lined_num, float fill_ratio, Game_map* game_map, Board_pattern* extra_info, int length)
{
	for (size_t i = 0; i < length; i++)
		Gen_data(lined_num,
			fill_ratio,
			game_map + i,
			extra_info + i).go();
}

Game_map* generate_data
(int num,int lined_num=4, float fill_ratio=0.5 )
{
	Game_map* game_map = new Game_map[num];
	Board_pattern* extra_info = new Board_pattern[num];
	if (num % THREAD_MAX_NUM != 0)
	{
		std::cout << "number of generated data should be divisible by Thread num" << std::endl;
		return nullptr;
	}
	int taskperthread = num / THREAD_MAX_NUM;
	std::vector< std::future<void> > results;
	for (int i = 0; i < THREAD_MAX_NUM ; i++)
		results.emplace_back(
			executor.enqueue
			(func,
				lined_num,
				fill_ratio,
				game_map + (i * taskperthread),
				extra_info + (i * taskperthread),
				taskperthread));
	for (auto&& task : results)
		task.get();
	extra_info->print();
	game_map->print();
	
	return game_map;
}

class Data_controller
{
	//TODO:数据类型转换到Python的格式
};