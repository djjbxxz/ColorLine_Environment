#pragma once
#include "Base.h"

class Game_rule
{
public:
	Game_rule(const Game_map* _before, Game_map* _after, Move _move) 
		:before(_before), after(_after),move(_move)
	{}
public:
	static std::vector<std::vector<Point>> Scan_all(const Game_map* game_map);
	int rule();
private:
	void Scan_all();
	static void Scan_Lined(const Point& point,std::vector<std::vector<Point>>&lineds, const Game_map* );
	std::vector<Point> Scan_Lined(const Point& point)const;
	void _move_act();
	int Addscore_eliminate();
	static std::vector<Color> get_next_three();
private:
	static void _scan_lined(const Point&point,Direction direction,std::vector<Point>&, const Game_map*);
private:
	const Game_map* before;
	Game_map* after;
	Move move;
	std::vector<std::vector<Point>>lineds;
};
