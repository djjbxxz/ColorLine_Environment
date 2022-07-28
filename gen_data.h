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



class Observation
{
public:
	Observation(int _lined_num, float _fill_ratio)//last
	{
		auto a = Gen_data(_lined_num, _fill_ratio, &_game_map);
		a.go();
		move = a.pattern._move;
#ifdef _DEBUG
		extra_info = a.pattern;
#endif
		valid_mask = std::move(Legal_mask(a.game_map).get_result());
	};
	Observation(const Observation& observation)//next
	{
		_game_map = observation._game_map;
		reward = Game_rule(&observation._game_map, &_game_map, observation.move).rule();
	};
	Observation(Observation&& o)noexcept
	{
		_game_map = std::move(o._game_map);
		move = std::move(o.move);
		reward = o.reward;
		valid_mask = std::move(o.valid_mask);
	}
	Observation() {};
	const Game_map& game_map()const { return _game_map; };
	Move move;
	int reward = 0;
	Moveable_mask valid_mask;
protected:
	Game_map _game_map;
public:
#ifdef _DEBUG
	Board_pattern extra_info;
#endif
};

class Transition
{
public:
	Transition(int _lined_num, float _fill_ratio)
		:_last(Observation(_lined_num, _fill_ratio)),
		move(_last.move),
		_next(_last)
	{
	};
	const Observation _last;
	int move;
	const Observation _next;
#ifdef _PRINT
	void print()const
	{
#ifdef _DEBUG
		_last.extra_info.print();
#endif
		_last.game_map().print();
		Move::from_densed(move).print();
		_next.game_map().print();
	}
#endif // _DEBUG
};

