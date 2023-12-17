#pragma once
#include "Base.h"


namespace Pathfinding
{
	class A_star;

	class Path_tree_Node;
};


class Pathfinding::A_star
{
	enum class GRID_STATU :char
	{
		NERVER_VISIT,
		WALL,
		IN_OPENLIST,
		IN_CLOSELIST
	};

public:
	class Path_tree_Node;
public:
	A_star(const Point& _startpoint, const Point& _endpoint, const Game_map& _game_map)
		:startpoint(_startpoint), endpoint(_endpoint)
	{
		game_map.set_all(GRID_STATU::NERVER_VISIT);
		for (int i = 0; i < CHESS_NUM; i++)
			game_map.set(i, _game_map[i] == Color::empty ? GRID_STATU::NERVER_VISIT : GRID_STATU::WALL);
	};
	A_star(const Lined_chess& lined_chess) :startpoint(lined_chess.startpoint), endpoint(lined_chess.destination)
	{
		for (const auto& point : lined_chess.points)
			game_map[point] = GRID_STATU::WALL;
	};
	std::vector<Point> get_path();
private:
	Path_tree_Node* algorithm_main();
	Path_tree_Node* get_point_from_openlist();
	std::vector<Point> get_reachable(const Point& point)const;
	void add_to_openlist(Point& point, Path_tree_Node* _last = nullptr);
private:
	Point startpoint;
	Point endpoint;
	_MAP<GRID_STATU> game_map;
	std::vector<Path_tree_Node*> openlist;
	std::vector<Path_tree_Node> all_points;
};

class Pathfinding::A_star::Path_tree_Node :public Point
{
public:
	Path_tree_Node(const Point& point, const Point& endpoint, const Path_tree_Node* _last = nullptr)
		:Point(point), g(0), h(0)
	{
		if (_last)
		{
			g = _last->g + 1;
			last = _last;
		}
		h = distance(endpoint);
	}
	Path_tree_Node(const Path_tree_Node& node)
		:Point(node), g(node.g), h(node.h), last(node.last) {};
	bool operator>(const Path_tree_Node& node)const { return f() > node.f(); }
	bool operator<(const Path_tree_Node& node)const { return f() < node.f(); }

	float f()const { return g + h; }
	bool update(const Path_tree_Node& parent)
	{
		auto new_g = parent.g + 1;
		if (new_g < g)
		{
			g = new_g;
			last = &parent;
			return true;
		}
		else
			return false;
	};
public:
	const Path_tree_Node* last = nullptr;
	std::vector<Point> get_path();
private:
	float g;//past cost
	float h;//estimated future cost
};
