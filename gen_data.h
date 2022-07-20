#pragma once
#include "Base.h"

class Board_pattern
{
public:
	Point startpoint;
	Point destination;
	std::vector<Point> lined;
	Point another_destination;
	std::vector<Point> path;
	std::vector<Point> other;
public:
	void set(Lined_chess& lined);
	void set_path(const std::vector<Point>& path);
#ifdef _PRINT
	void print();
#endif // DEBUG

};

class Gen_data
{
	class Return_message
	{
	public:
		Return_message(Game_map* _game_map, Board_pattern* _pattern) :game_map(_game_map), extra_info(_pattern) {};
		Game_map* game_map;
		Board_pattern* extra_info;
		~Return_message()
		{
			//delete game_map;
			//delete extra_info;
		}
#ifdef _PRINT
		void print() { extra_info->print(); game_map->print(); };
#endif // DEBUG
	};
public:
	Gen_data(int _lined_num, float _fill_ratio, Game_map* _game_map = nullptr , Board_pattern* _extra_info= nullptr)
		:lined_num(_lined_num), fill_ratio(_fill_ratio), game_map(_game_map), pattern(_extra_info)
	{
		if (!game_map)
		{
			game_map = new Game_map(); pattern = new Board_pattern();
		}
	}
	~Gen_data() {}
	Direction choos_a_direction(const Point& point);
	std::vector<Point> get_destination(Lined_chess& lined);
	Lined_chess get_lined_chess(Board_pattern&);
	void fill_empty();
	Return_message go();
	void paint();
#ifdef _PRINT
	void print();
#endif // DEBUG
public:
	Game_map* game_map;
	Board_pattern* pattern;
	void generate_data();
private:
	int lined_num;
	float fill_ratio;
};

