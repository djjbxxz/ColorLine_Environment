#pragma once
#include "Base.h"

class Game_rule
{
public:
	Game_rule(Game_map& _game_map, Move _move)
		:game_map(_game_map), move(_move)
	{
	}
public:
	static std::vector<std::vector<Point>> Scan_all(const Game_map& game_map);
	int rule();
private:
	static std::vector<std::vector<Point>> Scan_a_point(const Point& point, const Game_map& game_map);
	void _move_act();
	int Addscore_eliminate(const std::vector<std::vector<Point>>& ,bool);
	std::vector<Point> lay_three();
	std::vector<Point> get_empty();
	static std::vector<Color> get_next_three();
private:
	static void _scan_along_direction(const Point& point, Direction direction, std::vector<Point>&, const Game_map&);
private:
	Game_map& game_map;
	Move move;
};
