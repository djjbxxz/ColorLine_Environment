//#ifdef _DEBUG
//
//#else
#include <pybind11\pybind11.h>
#include "gen_data.h"
namespace py = pybind11;


#include "threadpool.h"


void func(int lined_num, float fill_ratio, Game_map* game_map, Board_pattern* extra_info, int length)
{
	for (size_t i = 0; i < length; i++)
		Gen_data(lined_num,
			fill_ratio,
			game_map + i,
			extra_info + i).go();
}

void generate_data
(int lined_num, float fill_ratio, Game_map* game_map, Board_pattern* extra_info, int num)
{
	if (num % THREAD_MAX_NUM != 0)
	{
		std::cout << "number of generated data should be divisible by Thread num" << std::endl;
		return;
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
}


//PYBIND11_MODULE(example1, m)
//{
//	m.doc() = "The general function";
//	m.def("age", &age);
//	m.def("Name", &Name);
//}

//#endif

