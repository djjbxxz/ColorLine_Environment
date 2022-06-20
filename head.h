#pragma once
#define DEBUG

#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#ifdef DEBUG
#include <assert.h>

#endif // DEBUG



constexpr auto BOARD_SIZE = 9;
//constexpr auto MIN_ELIM_NUM = 5;

enum color
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

struct Point
{
	char x, y;
	Point(char	_x, char _y) :x(_x), y(_y) {};
	Point(char index) { x = index / BOARD_SIZE; y = index % BOARD_SIZE; };
	Point(int index) { x = index / BOARD_SIZE; y = index % BOARD_SIZE; };
	Point() { x = -1; y = -1; };
	bool operator== (const Point a)const
	{
		return this->x == a.x && this->y == a.y;
	}
	Point operator+ (const Point a)
	{
		return { x + a.x, y + a.y };
	}
	Point operator+(const char* a)
	{
		return { x + *a, y + *(a + 1) };
	}
	Point operator-(const Point a)//¼õ·¨
	{
		return { x - a.x, y - a.y };
	}
	Point operator-()//È¡·´
	{
		return { -x,-y };
	}
	Point operator+=(const Point a)
	{
		return { x + a.x,y + a.y };
	}
	inline char index()const //return 1D index
	{
		return x * BOARD_SIZE + y;
	}
};

class Random
{
public:
	Random() {
		std::random_device rd;
		auto a_ptr = new std::mt19937(rd());
		mt = a_ptr;

		_random_color = new std::uniform_int_distribution<int>(1, 7);
		_random_max_100 = new std::uniform_int_distribution<int>(0, 100);
	}
	~Random()
	{
		delete mt;
		delete _random_color;
	}
	inline int rand_choice(int size)
	{
		std::uniform_int_distribution<int> dist(0, size);
		return dist(*mt);
	}
	inline color rand_color()
	{
		return color((*_random_color)(*mt));
	}
	inline char randint(int max)
	{
		#ifdef DEBUG
			assert(max<100  && max >0);
		#endif

		return (*_random_max_100)(*mt)%max;
	}
private:
	std::mt19937 *mt;
	std::uniform_int_distribution<int>* _random_color;
	std::uniform_int_distribution<int>* _random_max_100;
};
extern Random random_generator;

class game_map
{
public:
	game_map() 
	{
		_empty.reserve(BOARD_SIZE * BOARD_SIZE);
		data= std::vector<char>(BOARD_SIZE*BOARD_SIZE,0);
		for (char i=0;i<BOARD_SIZE*BOARD_SIZE;i++)
			_empty.emplace_back(Point{i/9,i%9});

	};
	game_map(float fill_ratio)
	{
		_empty.reserve(BOARD_SIZE * BOARD_SIZE);
		data = std::vector<char>(BOARD_SIZE * BOARD_SIZE, 0);
		for (char i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
			_empty.emplace_back(Point{ i / 9,i % 9 });

		int num_to_fill = BOARD_SIZE * BOARD_SIZE * fill_ratio;
		for (size_t i = 0; i < num_to_fill; i++)
		{
			auto index = random_generator.rand_choice(_empty.size());
			lay_chess(index,random_generator.rand_color());
		}
	}
	inline size_t size()
	{
		return data.size();
	}
public:
	void pick_a_spot();
	void lay_chess(const Point& point, color _color);
	void lay_chess(int, color _color);
	color inspect(const Point& point)const;
	color inspect(int)const;
private:
	void erase_from_empty(int);
	void erase_from_empty(const Point&);
private:
	std::vector<char> data;
	std::vector<Point> _empty;
public:
	void print();

	//empty
};

struct data
{
	char game_map;
	//move
	//reward
};


class Gen_data
{
public:
	Gen_data(Random* _random):random(_random) {  }
	~Gen_data() {}
public:
	void random_lay_chess(game_map map, char lay_num);
private:
	Random* random=&random_generator;
	const char scan_direction[8][2] = { {1,0},{0,1},{1,-1},{1,1},
									{-1,0},{0,-1},{-1,1},{-1,-1} };
};


class Matrix {
public:
	Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
		m_data = new float[rows * cols];
	}
	float* data() { return m_data; }
	size_t rows() const { return m_rows; }
	size_t cols() const { return m_cols; }
private:
	size_t m_rows, m_cols;
	float* m_data;
};
