#include "Game_rule.h"

std::vector<std::vector<Point>> Game_rule::Scan_all(const Game_map* game_map)
{
	std::vector<std::vector<Point>>lineds;
	FOR_RANGE(i, BOARD_SIZE)
		FOR_RANGE(j, BOARD_SIZE)
		if (game_map->get({ i,j }) != Color::empty)
			Scan_Lined({ i,j }, lineds, game_map);
	return lineds;
}

//call validate in advance
int Game_rule::rule()
{
	_move_act();
	auto try_lined = Scan_Lined(move.end);
	if (!try_lined.empty())
		lineds.push_back(std::move(try_lined));
	int score = Addscore_eliminate();
	if (score == 0)
		after->set_next_three(get_next_three());
	return score;
}

void Game_rule::Scan_all()
{
	lineds.clear();
	for (char i = 0; i < BOARD_SIZE; i++)
		for (char j = 0; j < BOARD_SIZE; j++)
			Scan_Lined({ i,j }, lineds, before);
}

void Game_rule::Scan_Lined(const Point& point, std::vector<std::vector<Point>>& lineds, const Game_map* game_map)
{
	for (auto&& direction : Direction::four_neighbor)
	{
		std::vector<Point>lined;
		_scan_lined(point, direction, lined, game_map);
		_scan_lined(point, -direction, lined, game_map);
		if (lined.size() >= 4)
		{
			lined.push_back(point);
			if (!myfunc::is_inlist(lined, lineds))
				lineds.push_back(std::move(lined));
		}
	}
}

void Game_rule::_move_act()
{
	auto& game_map = after;
	game_map->set(move.end, game_map->get(move.start));
	game_map->set(move.start, Color::empty);
}

int Game_rule::Addscore_eliminate()
{
	auto& game_map = after;
	int instant_reward = 0;
	for (auto&& lined : lineds)
	{
		for (auto&& point : lined)
		{
			game_map->set(point, Color::empty);
			instant_reward += 2;
		}
	}
	return instant_reward;
}

void Game_rule::_scan_lined(const Point& point, Direction direction, std::vector<Point>& lined, const Game_map* game_map)
{
	Point new_point = point;
	while (true)
	{
		new_point = direction.walk(new_point, 1);
		if (new_point.outofrange())
			break;
		if (game_map->get(point) == game_map->get(new_point))
			lined.push_back(new_point);
		else
			break;
	}
}

std::vector<Point> Game_rule::Scan_Lined(const Point& point)const
{
	auto& game_map = before;
	for (auto&& direction : Direction::four_neighbor)
	{
		std::vector<Point>lined;
		_scan_lined(point, direction, lined, before);
		_scan_lined(point, -direction, lined, before);
		lined.push_back(point);
		if (lined.size() >= 5)
			return lined;
	}
	return std::vector<Point>();
}

std::vector<Color> Game_rule::get_next_three()
{
	auto next_three = std::vector<Color>();
	next_three.reserve(3);
	for (int i = 0; i < 3; i++)
		next_three.push_back(Color::rand_color());
	return next_three;
}