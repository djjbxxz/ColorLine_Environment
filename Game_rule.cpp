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
	int score = try_move_score();
	lay_coming_chess();
	if (is_game_end)
		return -1;

	game_map.set_coming_chess(get_coming_chess());

return is_game_end ? -1 : score;
}

std::vector<Point> Game_rule::lay_coming_chess()
{
	std::vector<Point>_wheres;
	auto empty = get_empty();
	for (auto&& color : game_map.coming_chess)
	{
		if (empty.empty())
		{
			is_game_end = true;
			break;
		}
		auto index = Random::randint(empty.size());
		auto& _where = empty[index];
		game_map.set(_where, color);
		_wheres.push_back(_where);
		empty.erase(empty.begin() + index);
	}
	if (empty.empty())
		is_game_end = true;
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
		if (lined.size() >= MIN_ELEMINATABLE_NUM)
			temp.push_back(lined);
	}
	return 	temp;
}

void Game_rule::_move_act()
{
	game_map.set(move.target, Color::rand_color());
}

int Game_rule::Addscore()
{
	int instant_reward = 0;
	if (move.target.x < 3)
		instant_reward += 2;
	else
		instant_reward -= 2;
	return instant_reward;
}

int Game_rule::try_move_score()
{
	bool flag = game_map.get(move.target) == Color::empty;
	int score = 0;
	if (flag)
	{
		_move_act();
		score = Addscore();
	}
	else
	{
		//illegal move
		score = -2;
	}
	return score;
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


std::array<Color, COMING_CHESS_NUM> Game_rule::get_coming_chess()
{
	std::array<Color, COMING_CHESS_NUM>coming_chess;
	FOR_RANGE(i, COMING_CHESS_NUM)
		coming_chess[i] = Color::rand_color();
	return coming_chess;
}