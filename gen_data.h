#pragma once
#include "Base.h"
#include "Game_rule.h"
#include "legel_mask.h"
class Board_pattern
{
public:
	Board_pattern() { reset(); }
	Move _move;
	std::vector<Point> lined;
	Point another_destination;
	std::vector<Point> path;
	std::vector<Point> other;
public:
	void set(Lined_chess& lined);
	void set_path(const std::vector<Point>& path);
	void reset() {
		another_destination = Point();
		lined.clear();
		path.clear();
		other.clear();
	}
#ifdef _PRINT
public:
	void print()const;
#endif // DEBUG

};

class Gen_data
{
	public:
	Gen_data(int _lined_num, float _fill_ratio, Game_map* _game_map)
		:lined_num(_lined_num), fill_ratio(_fill_ratio), game_map(_game_map) {}
	~Gen_data() {}
	Direction choos_a_direction(const Point& point);
	std::vector<Point> get_destination(Lined_chess& lined);
	Lined_chess get_lined_chess();
	void fill_empty();
	void set_rand_next_three();
	void go();
	void paint();
	void reset() {
		game_map->reset();
		pattern.reset();
	}
#ifdef _PRINT
	void print();
#endif // DEBUG
private:
	bool validate()const;
public:
	Game_map* game_map;
	Board_pattern pattern;
private:
	int lined_num;
	float fill_ratio;
};
