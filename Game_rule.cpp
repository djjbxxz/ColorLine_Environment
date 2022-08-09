#include "Game_rule.h"
std::vector<std::vector<Point>> Game_rule::Scan_all(const Game_map& game_map)
{
	std::vector<std::vector<Point>>lineds;
	FOR_RANGE(i, BOARD_SIZE)
		FOR_RANGE(j, BOARD_SIZE)
		if (game_map.get({ i,j }) != Color::empty)
			Scan_a_point({ i,j }, game_map);
	return lineds;
}

//call validate in advance
int Game_rule::rule()
{
	_move_act();
	auto lined = Scan_a_point(move.end, game_map);
	int score = Addscore_eliminate(lined, true);
	if (score == 0)
	{
		auto lineds = std::vector<std::vector<Point>>();
		auto _where = lay_three();
		for (auto&& point : _where)
		{
			auto lined = Scan_a_point(point, game_map);
			lineds.insert(lineds.end(), lined.begin(), lined.end());
		}
		Addscore_eliminate(lineds, false);
		game_map.set_next_three(get_next_three());
	}
	return score;
}

std::vector<Point> Game_rule::lay_three()
{
	std::vector<Point>_wheres;
	auto empty = get_empty();
	for (auto&& color : game_map.next_three)
	{
		if (empty.empty())
			break;
		auto index = Random::randint(empty.size());
		auto& _where = empty[index];
		game_map.set(_where, color);
		_wheres.push_back(_where);
		empty.erase(empty.begin() + index);
	}
	return _wheres;
}

std::vector<Point> Game_rule::get_empty()
{
	auto temp = std::vector<Point>();
	FOR_RANGE(i, game_map._data.size())
		if (game_map._data[i] == Color::empty)
			temp.emplace_back(i);
	return temp;
}


std::vector<std::vector<Point>> Game_rule::Scan_a_point(const Point& point, const Game_map& game_map)
{
	std::vector<std::vector<Point>>temp;
	for (auto&& direction : Direction::scan_direction)
	{
		std::vector<Point>lined;
		_scan_along_direction(point, direction, lined, game_map);
		_scan_along_direction(point, -direction, lined, game_map);
		lined.push_back(point);
		if (lined.size() >= 5)
			temp.push_back(lined);
	}
	return 	temp;
}

void Game_rule::_move_act()
{
	game_map.set(move.end, game_map.get(move.start));
	game_map.set(move.start, Color::empty);
}

int Game_rule::Addscore_eliminate(const std::vector<std::vector<Point>>& lineds, bool add_score)
{
	int instant_reward = 0;
	for (auto&& lined : lineds)
	{
		for (auto&& point : lined)
		{
			if (game_map.get(point) != Color::empty)
			{
				game_map.set(point, Color::empty);
				if (add_score)
					instant_reward += 2;
			}
		}
	}
	return instant_reward;
}

void Game_rule::_scan_along_direction(const Point& point, Direction direction, std::vector<Point>& lined, const Game_map& game_map)
{
	Point new_point = point;
	while (true)
	{
		new_point = direction.walk(new_point, 1);
		if (new_point.outofrange())
			break;
		if (game_map.get(point) == game_map.get(new_point))
			lined.push_back(new_point);
		else
			break;
	}
}


std::vector<Color> Game_rule::get_next_three()
{
	auto next_three = std::vector<Color>();
	next_three.reserve(3);
	for (int i = 0; i < 3; i++)
		next_three.push_back(Color::rand_color());
	return next_three;
}