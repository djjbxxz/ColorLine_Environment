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
		void reset() { _data = {}; };
	};
public:
	Moveable_mask get_result()const {
		return mask;
	};
	Legal_mask(const Game_map& _game_map) :game_map(_game_map) {
		mask = Moveable_mask(BOARD_SIZE * BOARD_SIZE, false);
		go();
	}
	static Move get_random_move(const Moveable_mask& mask)
	{
		std::vector<int>temp;
		temp.reserve(mask.size());
		FOR_RANGE(i, mask.size())
		{
			if (mask[i])
				temp.push_back(i);
		}
		return Move(Random::rand_choice(temp));
	}
private:
	void GetEmptySet();
	void go();

	void GetBeginSet();
	void MakeResult();
	void calculate(const std::vector<Point>& start, const std::vector<Point>& end);
	std::vector<Point> grow_to_max(const Point& startpoint, bool_map& scaned_map);

private:
	const Game_map& game_map;
	Moveable_mask mask;
	std::vector<std::vector<Point>>emptyset;
	std::vector<std::vector<Point>>startset;
};
