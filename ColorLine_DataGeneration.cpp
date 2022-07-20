#ifndef _EXPORT



#include <iostream>
#include "gen_data.h"
#include "Export.h"
//void init(void)
//{
//	srand(time(NULL));
//	std::cout << "Dll initialized!" << std::endl;
//}
int main()
{
#ifdef _DEBUG
	std::cout << "DEBUG\n";
#else
	std::cout << "No DEBUG\n";
#endif

	int lined_num = 3;
	float fill_ratio = 0.99;

#ifdef _DEBUG
	//auto result = Gen_data(lined_num, fill_ratio).go();
	//result.print();

	//int times = 3000;

	//for (int i = 0; i < times; i++)
	//	Gen_data(4, 0.6).go();
#else

	int times = 10000;

	//for (int i=0;i<times;i++)
	//	Gen_data(lined_num, fill_ratio).go();
	Game_map* game_map = new Game_map[times];
	Board_pattern* extra_info = new Board_pattern[times];
	generate_data(lined_num, fill_ratio, game_map, extra_info, times);
	int offset = times/THREAD_MAX_NUM-1;
	(extra_info + offset)->print();
	(game_map + offset)->print();
	offset = times / THREAD_MAX_NUM ;
	(extra_info + offset)->print();
	(game_map + offset)->print();
#endif
	//a.print();

}
#endif

