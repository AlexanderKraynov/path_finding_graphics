#ifndef ASSIGNMENT_DFS_HPP
#define ASSIGNMENT_DFS_HPP

#include <unordered_map>
#include "PathFinder.hpp"

class Dfs : public PathFinder
{
public:
  Dfs(int rows, int columns);
  std::list<std::pair<int, int>> pathBetween(std::pair<int, int> origin, std::pair<int, int> destination) override;
};


#endif
