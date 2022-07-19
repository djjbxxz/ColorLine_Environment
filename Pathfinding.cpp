#include "Pathfinding.h"
using Pathfinding::A_star;
using Pathfinding::BSTNode;
using Pathfinding::Sorted_list;

std::vector<Point> A_star::get_path()
{
	return algorithm_main()->get_path();
}

A_star::Path_tree_Node* A_star::algorithm_main()
{
	all_points.reserve(BOARD_SIZE * BOARD_SIZE);
	add_to_openlist(startpoint, endpoint);
	while (!openlist.empty())
	{
		auto &point = *get_point_from_openlist();
		if (point == endpoint)
			return &point;
		auto reachables = get_reachable(point);
		for (auto& reachable_point : reachables)
		{
			if (get_game_map(reachable_point) == GRID_STATU::NERVER_VISIT)
			{
				add_to_openlist(reachable_point, endpoint, &point);
			}
			else
			{
				for (const auto& openlist_point : openlist)
					if (*openlist_point == reachable_point)
						openlist_point->update(point);
			}
		}
	}
#ifdef _DEBUG
	assert(true);//No path found

#endif // DEBUG

}

A_star::Path_tree_Node* A_star::get_point_from_openlist()
{
	std::sort(openlist.begin(), openlist.end(),
		[&](const Path_tree_Node* a,
			const Path_tree_Node* b)->bool
		{return a->f() > b->f(); });
	Path_tree_Node* point = openlist.back();
	openlist.pop_back();
	set_game_map(*point, GRID_STATU::IN_CLOSELIST);
	return point;
}

std::vector<Point> A_star::get_reachable(const Point& point) const
{
	std::vector<Point>temp;
	for (const auto& each_direction : Direction::four_direction)
	{
		auto next_point = each_direction.walk(point, 1);
		auto statu = get_game_map(next_point);
		if (!next_point.outofrange() && (statu == GRID_STATU::NERVER_VISIT || statu == GRID_STATU::IN_OPENLIST))
			temp.emplace_back(next_point);
	}
	return temp;
}

A_star::GRID_STATU A_star::get_game_map(const Point& point) const
{
	return game_map[point.x][point.y];
}


void A_star::set_game_map(const Point& point, GRID_STATU statu)
{
	game_map[point.x][point.y] = statu;
}

A_star::Path_tree_Node* Pathfinding::A_star::add_to_openlist(Point &point, Point &endpoint, Path_tree_Node* _last)
{
	all_points.emplace_back(point,endpoint,_last);
	set_game_map(point, GRID_STATU::IN_OPENLIST);
	A_star::Path_tree_Node* p_point = &*(all_points.end()-1);
	openlist.push_back(p_point);
	return p_point;
}

template<typename T>
const T& BSTNode<T>::max() const
{
	if (rchild)
		return rchild->max();
	else
		return value;
}

template<typename T>
const T& BSTNode<T>::min() const
{
	if (lchild)
		return rchild->max();
	else
		return value;
}

template<typename T>
BSTNode<T>* BSTNode<T>::insert(T insert_value)const
{
	if (insert_value > value)
	{
		if (rchild)
			rchild->insert(insert_value);
		else
			rchild = new BSTNode(insert_value);
	}
	else if (insert_value == value)
	{
		if (!lchild)
			lchild = new BSTNode(insert_value);
		else if (!rchild)
			rchild = new BSTNode(insert_value);
		else
		{
			auto old = lchild;
			lchild = new BSTNode(insert_value);
			lchild->lchild = old;
		}
	}
	else if (insert_value < value)
	{
		if (lchild)
			lchild->insert(insert_value);
		else
			lchild = new BSTNode(insert_value);
	}
	else
	{

#ifdef _DEBUG
		assert(true);
#endif // DEBUG
		return nullptr;
	}
}

template<typename T>
void BSTNode<T>::remove() const
{
	if (lchild)
		lchild->remove();
	if (rchild)
		rchild->remove();
	delete this;
}

template<typename T>
void Sorted_list<T>::insert(const T& value)const
{
	if (!root)
		root = new BSTNode<T>{ value };
	else
		root->insert(value);
}

template<typename T>
const T& Sorted_list<T>::max()const
{
	if (root)
		return root->max();
#ifdef _DEBUG
	else
		assert(true);

#endif // DEBUG

}

template<typename T>
const T& Sorted_list<T>::min()const
{
	if (root)
		return root->min();
#ifdef _DEBUG
	else
		assert(true);
#endif // DEBUG
}

template<typename T>
void Sorted_list<T>::clear()
{
	if (root)
		root->remove();
}

std::vector<Point> Pathfinding::A_star::Path_tree_Node::get_path()
{
	std::vector <Point>path_reverse;
	const Path_tree_Node* ptr = this;
	while (ptr)
	{
		path_reverse.emplace_back(ptr->x, ptr->y);
		ptr = ptr->last;
	}
	std::vector <Point>path;
	path.reserve(path_reverse.size());
	for (int Index = path_reverse.size() - 1; Index >= 0 ; Index--)
	{
		path.push_back(path_reverse[Index]);
	}
	return path;
}
