#pragma once

#include "my_func.h"
#include <map>


using myfunc::Random;

constexpr auto BOARD_SIZE = 9;

class Color {
	enum class _color :char
	{
		empty = 0,
		green = 1,
		red = 2,
		dark_blue = 3,
		yellow = 4,
		light_blue = 5,
		purple = 6,
		brown = 7
	};
public:
	Color(_color _value) :value(_value) {};
	Color() :value(_color::empty) {};
public:
	_color value;
	static const std::vector<Color> all_color;
	static const std::vector<Color> all_statu;
	static const Color empty;
public:
	static Color rand_color_except(std::vector<Color>& exclusion);
	static Color rand_color_except(Color _color);
	static Color rand_color();
	//static Color rand_statu();
	static Color rand_statu_except(Color _color);
	bool operator== (const Color& a)const
	{
		return this->value == a.value;
	}
#ifdef _PRINT
	int print() { return (int)value; };
#endif // DEBUG
};


class Point
{
public:
	char x, y;
	Point(char	_x, char _y) :x(_x), y(_y) {};
	Point(char index) { x = index / BOARD_SIZE; y = index % BOARD_SIZE; };
	Point(int index) { x = index / BOARD_SIZE; y = index % BOARD_SIZE; };
	//Point() =delete;
	Point() { x = -1; y = -1; };
	bool operator== (const Point& a)const
	{
		return this->x == a.x && this->y == a.y;
	}
	bool operator!= (const Point& a)const
	{
		return this->x != a.x || this->y != a.y;
	}
	Point operator+ (const Point& a)const
	{
		return { x + a.x, y + a.y };
	}
	Point operator*(const char step)const
	{
		return { x * step,y * step };
	}
	Point operator-(const Point& a)const//¼õ·¨
	{
		return { x - a.x, y - a.y };
	}
	Point operator-()const//È¡·´
	{
		return { -x,-y };
	}
	Point operator+=(const Point& a)
	{
		return { x + a.x,y + a.y };
	}
	inline char index()const //return 1D index
	{
		return x * BOARD_SIZE + y;
	}
	bool outofrange()const
	{
		return x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE;
	}
	Point walk(const Point& offset, int step)const
	{
		return{ *this + offset * step };
	}
	Point walk_r(const Point& offset, int step)const
	{
		return{ *this - offset * step };
	}
	float distance(const Point& point)const
	{
		return std::sqrt(std::pow((point.x - x), 2) + std::pow((point.y - y), 2));
	}
#ifdef _PRINT
	void print()const { printf("(%d,%d)", (int)x, (int)y); };
#endif // DEBUG

private:

};


class Direction
{
public:
	enum class _direction :char
	{
		north,
		northeast,
		east,
		southeast,
		south,
		southwest,
		west,
		northwest,
	};
public:
	Direction(_direction d) :direction(d) {};
	Direction() :direction(_direction::north) {};
public:
	_direction direction;
	const Point& point()const { return direct2point.find(direction)->second; };
	Point walk(const Point& startpoint, int step)const { return startpoint.walk(point(), step); }
	Point walk_r(const Point& startpoint, int step)const { return startpoint.walk(-point(), step); }//walk reversely
public:
	static const std::map < Direction::_direction, Point > direct2point;
	static const std::vector <Direction> eight_direction;
	static const std::vector <Direction> four_direction;

};


class Game_map
{
public:
	Game_map()
	{
		data = std::vector<Color>(81);
	};
public:
	const Point& pick_a_spot(const std::vector<Point>& exclusion)const;
	const Point& pick_a_spot()const;
	void set(const Point& point, Color _color);
	void set(std::vector<Point>& points, Color _color);
	void lay_chess(int, Color _color);
	const Color& get(const Point& point)const;
	const Color& operator[](int i)const;
	const Color& get(int row, int colomn)const;
public:
	const static std::vector<Point> _empty;
private:
	static std::vector<Point> _empty_init();
private:
	std::vector<Color> data;
#ifdef _PRINT
public:
	void print();
#endif // _DEBUG
};



class Lined_chess
{
public:
	Lined_chess(Game_map* game_map, Point lined_startpoint, Direction _lined_direction, int _lined_num) :
		endpoint1(lined_startpoint),
		lined_direction(_lined_direction),
		lined_num(_lined_num)
	{
		endpoint2 = _lined_direction.walk(lined_startpoint, _lined_num - 1);
		points.reserve(_lined_num);
		points.push_back(endpoint1);
		for (int i = 0; i < _lined_num - 1; i++)
			points.emplace_back(_lined_direction.walk(endpoint1, i + 1));
		std::vector<Point> not_safe_destinations;
		not_safe_destinations.emplace_back(lined_direction.walk(endpoint2, 1));
		not_safe_destinations.emplace_back(lined_direction.walk_r(endpoint1, 1));
		for (auto& point : not_safe_destinations)
			if (!point.outofrange())
				possible_destinations.emplace_back(point);
		if (possible_destinations.empty())
			return;
		destination = Random::rand_choice(possible_destinations);
		exclusion.insert(exclusion.end(), points.begin(), points.end());
		exclusion.insert(exclusion.end(), possible_destinations.begin(), possible_destinations.end());
		startpoint = game_map->pick_a_spot(exclusion);
		exclusion.emplace_back(startpoint);
#ifdef _DEBUG
		assert(!myfunc::is_inlist(startpoint, points));
#endif // _DEBUG

	}
	Lined_chess() {};
public:
	int lined_num;
	Direction lined_direction;
	Point endpoint1;
	Point endpoint2;
	Point startpoint;
	Point destination;
	std::vector<Point> possible_destinations;
	std::vector<Point> points;
	std::vector<Point>exclusion;
private:

};

//template bool myfunc::is_inlist<Point>(const Point& a, const std::vector<Point>& list);
