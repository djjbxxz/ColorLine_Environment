#include "gen_data.h"
#include <iostream>
#include "Pathfinding.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <sstream>
#include <string>
#include <iostream>
#include "CompileTimeMsg.h"
#include <pybind11/numpy.h>

constexpr auto INPUT_CHANNEL_SIZE = (1 + COMING_CHESS_NUM) * COLOR_NUM;
namespace export_bind
{
	class game_statu_9928
	{
	public:
		game_statu_9928() {
			int* t = (int*)value;
			FOR_RANGE(i, BOARD_SIZE * BOARD_SIZE * INPUT_CHANNEL_SIZE)
				* (t + i) = 0;
		};
		game_statu_9928(const Game_map& game_statu) {
			auto game_map = game_statu._data;
			auto coming_chess = game_statu.coming_chess;
			int* ptr_game_map_9928 = (int*)value;
			FOR_RANGE(i, BOARD_SIZE * BOARD_SIZE * INPUT_CHANNEL_SIZE)
				* (ptr_game_map_9928 + i) = 0;


			for (int index = 0; index < COMING_CHESS_NUM; index++)
			{
				int color = (int)coming_chess[index];
				for (int i = 0; i < BOARD_SIZE; i++)
				{
					for (int j = 0; j < BOARD_SIZE; j++)
					{
						value[i][j][(COLOR_NUM - 1) + index * COLOR_NUM + color] = 1;
					}
				}

			}

			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					int t = (int)game_map[i * BOARD_SIZE + j];
					if (t)
						value[i][j][t - 1] = 1;
				}
			}
		}
		int value[BOARD_SIZE][BOARD_SIZE][INPUT_CHANNEL_SIZE];
	};
	class Point_int
	{
	public:
		Point_int() = delete;
		Point_int(const Point& point) :x(point.x), y(point.y) {};
		Point_int(int x, int y) :x(x), y(y) {};
		int x;
		int y;
	};
	Game_map generate_data(int lined_num, float fill_ratio)
	{
		lined_num = lined_num >= 2 ? lined_num : 2;
		lined_num = lined_num <= 8 ? lined_num : 8;
		fill_ratio = fill_ratio >= 0.05 ? fill_ratio : 0.05;
		fill_ratio = fill_ratio < 0.99 ? fill_ratio : 0.99;
		Game_map game_map;
		auto a = Gen_data(lined_num, fill_ratio, &game_map);
		a.go();
		return game_map;
	}

	Moveable_mask get_valid_mask(const Game_map& game_map)
	{
		return Legal_mask(game_map).get_result();
	}
	game_statu_9928 _994_to_9928(const Game_map& game_map)
	{
		return game_statu_9928(game_map);
	}
	int rule(Game_map& game_map, int move)
	{
		return Game_rule(game_map, Move(move)).rule();
	}

	auto get_path(pybind11::array_t<int> array, int move)
	{
		pybind11::buffer_info info = array.request();

		int* data = static_cast<int*>(info.ptr);
		int size = info.size;
		Move move_ = Move(move);
		auto start = move_.start;
		auto end = move_.end;
		auto path = Pathfinding::A_star{ start, end,{ data } }.get_path();
		return std::vector<Point_int>(path.begin(), path.end());
	}

	void seed(int seed)
	{
		Random::seed(seed);
	}
}
