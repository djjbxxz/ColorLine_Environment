#pragma once
#include "Base.h"

typedef std::vector<int> Moveable_mask;

class Legal_mask
{
private:
	class bool_map :public _MAP<bool>
	{
	public:
		bool_map() { reset(); }
		void reset() { _data = std::vector<bool>(BOARD_SIZE * BOARD_SIZE, false); };
	};
public:
	Moveable_mask get_result()const {
		return mask;
	};
	Legal_mask(Game_map* _game_map) :game_map(_game_map) {
		mask = Moveable_mask(POTENTIAL_MOVE_NUM, false);
		go();
	}
private:
	void GetEmptySet();
	void go();

	void GetBeginSet();
	void MakeResult();
	void calculate(const std::vector<Point>& start, const std::vector<Point>& end);
	std::vector<Point> grow_to_max(const Point& startpoint, bool_map& scaned_map);

private:
	const Game_map* game_map;
	Moveable_mask mask;
	std::vector<std::vector<Point>>emptyset;
	std::vector<std::vector<Point>>startset;
};
