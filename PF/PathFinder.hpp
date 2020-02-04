#ifndef ASSIGNMENT_PATHFINDER_HPP
#define ASSIGNMENT_PATHFINDER_HPP

#include <list>
#include <unordered_set>

#define PAIR_HASH_CONST 31

class PathFinder
{
public:
  struct pair_hash
  {
    inline int operator()(const std::pair<int, int> &v) const
    {
      return v.first * PAIR_HASH_CONST + v.second;
    }
  };

  PathFinder(int rows, int columns) : rows(rows), columns(columns), obstacles()
  {
  }

  using Point = std::pair<int, int>;
  using obstacles_set  = std::unordered_set<std::pair<int, int>, pair_hash>;
  virtual obstacles_set getObstacles() const;
  virtual bool isObstacle(const std::pair<int, int> &coordinates) const;
  virtual void addObstacle(const std::pair<int, int> &coordinates);
  virtual void removeObstacle(const std::pair<int, int> &coordinates);
  virtual std::list<std::pair<int, int>>
  pathBetween(const std::pair<int, int> &origin, const std::pair<int, int> &destination) = 0;
  virtual ~PathFinder() = default;
protected:
  obstacles_set obstacles;
  int rows;
  int columns;
};

#endif
