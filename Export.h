#include "gen_data.h"
#include <iostream>


constexpr auto INPUT_CHANNEL_SIZE = COLOR_NUM * (1+COMING_CHESS_NUM);
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
						value[(COLOR_NUM - 1) + index * COLOR_NUM + color][i][j] = 1;
					}
				}

			}

			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					int t = (int)game_map[i * BOARD_SIZE + j];
					if (t)
						value[t - 1][i][j] = 1;
				}
			}
		}
		int value[INPUT_CHANNEL_SIZE][BOARD_SIZE][BOARD_SIZE];
	};

	Game_map generate_data(int lined_num, float fill_ratio)
	{
		lined_num = lined_num >= 2 ? lined_num : 2;
		lined_num = lined_num <= 8 ? lined_num : 8;
		fill_ratio = fill_ratio >= 0.05 ? fill_ratio : 0.05;
		fill_ratio = fill_ratio < 0.99 ? fill_ratio : 0.99;
		Game_map game_map;
		//auto a = Gen_data(lined_num, fill_ratio, &game_map);
		//a.go();
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
}
