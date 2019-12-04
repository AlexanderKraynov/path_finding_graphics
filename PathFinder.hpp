
#ifndef ASSIGNMENT_PATHFINDER_HPP
#define ASSIGNMENT_PATHFINDER_HPP

#include <list>
#include <unordered_set>

class PathFinder
{
public:
  struct pair_hash
  {
    inline int operator()(const std::pair<int, int> &v) const
    {
      return v.first * 31 + v.second;
    }
  };

  PathFinder(int rows, int columns) : rows(rows), columns(columns), obstacles()
  {
  }

  using obstacles_set  = std::unordered_set<std::pair<int, int>, pair_hash>;
  virtual obstacles_set getObstacles();
  virtual bool isObstacle(std::pair<int, int> coordinates);
  virtual void addObstacle(std::pair<int, int> coordinates);
  virtual void removeObstacle(std::pair<int, int> coordinates);
  virtual std::list<std::pair<int, int>> pathBetween(std::pair<int, int> origin, std::pair<int, int> destination) = 0;
protected:
  obstacles_set obstacles;
  int rows;
  int columns;
};

#endif
