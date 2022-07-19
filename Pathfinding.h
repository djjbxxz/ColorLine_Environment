#pragma once
#include "Base.h"


namespace Pathfinding
{
	class Path;
	class A_star;
	template <typename T>
	class BSTNode;
	//class Point_A_star;
	//template <typename T>
	//typename BSTNode<Point_A_star> Sorted_list;
	template <typename T>
	class Sorted_list;
	class Path_tree_Node;
};


class Pathfinding::A_star
{
	enum class GRID_STATU:char
	{
		NERVER_VISIT,
		WALL,
		IN_OPENLIST,
		IN_CLOSELIST
	};

public:
	class Path_tree_Node;
public:
	A_star(const Lined_chess& lined_chess):startpoint(lined_chess.startpoint),endpoint(lined_chess.destination)
	{
		for (const auto& point : lined_chess.points)
			set_game_map(point, GRID_STATU::WALL);
	};
	std::vector<Point> get_path();
private:
	Path_tree_Node* algorithm_main();
	Path_tree_Node* get_point_from_openlist();
	std::vector<Point> get_reachable(const Point& point)const;
	GRID_STATU get_game_map(const Point& point)const;
	void set_game_map(const Point& point, GRID_STATU);
	Path_tree_Node* add_to_openlist(Point &point, Point &endpoint, Path_tree_Node* _last =nullptr);
private:
	Point startpoint;
	Point endpoint;
	GRID_STATU game_map[BOARD_SIZE][BOARD_SIZE]{GRID_STATU::NERVER_VISIT};
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

template <typename T>
class Pathfinding::BSTNode
{// Binary search tree node
public:
	BSTNode<T>* lchild;
	BSTNode<T>* rchild;
	T value;

public:
	BSTNode(T _value) :value(_value) { lchild = nullptr; rchild = nullptr; };
	//void operator delete(void* p)
	//{
	//	auto _p = (BSTNode*)p;
	//	if (_p->lchild)
	//		delete (void*)lchild;
	//	if (_p->rchild)
	//		delete (void*)rchild;
	//	free(_p);
	//};
	BSTNode* insert(T value)const;
	const T& max()const;
	const T& min()const;
	void remove()const;
};

template <typename T>
class Pathfinding::Sorted_list
{
public:
	Sorted_list() :root{ nullptr } {};
	Sorted_list(T value) { root = new BSTNode<T>{ value }; };
	void insert(const T& value)const;
	const T& max()const;
	const T& min()const;
	void clear();

private:
	BSTNode<T>* root;
};