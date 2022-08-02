#include "gen_data.h"
#include <iostream>

#include "threadpool.h"


namespace export_bind
{
	class game_statu_9928
	{
	public:
		game_statu_9928() {
			int* t = (int*)value;
			FOR_RANGE(i, 9 * 9 * 28)
				* (t + i) = 0;
		};
		int value[9][9][28];
	};
	class Data_pack :public Transition
	{
	public:
		Data_pack(int _lined_num, float _fill_ratio) :Transition(_lined_num, _fill_ratio)
		{
			last = &_last.game_map();
			last_3 = &_last.game_map().next_three;
			last_mask = &_last.valid_mask;
			next = &_next.game_map();
			next_3 = &_next.game_map().next_three;
			next_mask = &_next.valid_mask;
			reward = _next.reward;

			convert_to_9928(last->_data, *last_3, last_game_statu.value);
		}
		const Game_map* last;
		const std::vector<Color>* last_3;
		const Moveable_mask* last_mask;
		const Game_map* next;
		const std::vector<Color>* next_3;
		const Moveable_mask* next_mask;
		int reward;
		game_statu_9928 last_game_statu;
	public:
		static void convert_to_9928(const std::vector<Color>& game_map, const std::vector<Color>& next_three, int game_map_9928[9][9][28]);
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

	Data_pack* generate_data(int num, int lined_num, float fill_ratio)
	{
		return func(lined_num,fill_ratio);
	}

	Data_pack* get_result(int index)
	{
		return results[index].get();
	}

	void delete_data(Data_pack* data)
	{
		delete data;
	}


	void Data_pack::convert_to_9928(const std::vector<Color>& game_map, const std::vector<Color>& next_three, int game_map_9928[9][9][28])
	{
		int* ptr_game_map_9928 = (int*)game_map_9928;
		FOR_RANGE(i, 9 * 9 * 28)
			* (ptr_game_map_9928 + i) = 0;


		for (int index = 0; index < 3; index++)
		{
			int color = (int)next_three[index];
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					game_map_9928[i][j][6 + index * 7 + color] = 1;
				}
			}

		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int t = (int)game_map[i * BOARD_SIZE + j];
				if (t)
					game_map_9928[i][j][t - 1] = 1;
			}
		}

	}
}
