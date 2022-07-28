#include "gen_data.h"
#include <iostream>

#include "threadpool.h"


namespace export_bind
{
	class Data_pack :public Transition
	{
	public:
		Data_pack(int _lined_num, float _fill_ratio) :Transition(_lined_num, _fill_ratio)
		{
			last = &_last.game_map();
			last_mask = &_last.valid_mask;
			next = &_next.game_map();
			next_mask = &_next.valid_mask;
			reward = _next.reward;
		}
		const Game_map* last;
		const Moveable_mask* last_mask;
		const Game_map* next;
		const Moveable_mask* next_mask;
		int reward;
	public:
		static std::vector<Data_pack*>all_data;
	};

	std::vector<Data_pack*> Data_pack::all_data;

	Data_pack* func(int lined_num, float fill_ratio)
	{
		return new Data_pack(lined_num, fill_ratio);
	}
	class Task
	{
	public:
		Task(int _length, int _startpoint = 0) :startpoint(_startpoint), length(_length) {}
		int startpoint = 0;
		int length = 0;
		std::vector<Task>distribute()
		{
			int num_task_tofinfish = length;
			int statpoint = 0;
			int num_worker_left = THREAD_MAX_NUM;
			auto thread_work_list = std::vector<Task>();
			for (int i = 0; i < THREAD_MAX_NUM; i++)
			{
				int task_length = num_task_tofinfish / num_worker_left ? num_task_tofinfish / num_worker_left : 1;
				thread_work_list.emplace_back(statpoint, task_length);
				num_worker_left--;
				num_task_tofinfish -= task_length;
				statpoint += task_length;
				if (num_task_tofinfish == 0)
					break;
			}
			return thread_work_list;
		}

	};

	std::vector< std::future<Data_pack*> > results;

	void generate_data(int num, int lined_num, float fill_ratio)
	{
		results.clear();
		results.reserve(num);
		for (int i = 0; i < num; i++)
		{
			results.emplace_back(
				executor.enqueue
				(func,
					lined_num,
					fill_ratio
				));
		}
	}

	Data_pack* get_result(int index)
	{
		return results[index].get();
	}
}