#ifndef ASSIGNMENT_DFS_HPP
#define ASSIGNMENT_DFS_HPP

#include <unordered_map>
#include "PathFinder.hpp"

class Dfs : public PathFinder
{
public:
  Dfs(int rows, int columns);
  std::list<Point> pathBetween(const Point &origin, const Point &destination) override;
};


#endif
