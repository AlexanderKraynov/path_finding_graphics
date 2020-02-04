#include "PathFinder.hpp"

std::unordered_set<std::pair<int, int>, PathFinder::pair_hash> PathFinder::getObstacles() const
{
  return obstacles;
}

bool PathFinder::isObstacle(const std::pair<int, int> &coordinates) const
{
  return obstacles.find(coordinates) != obstacles.end();
}

void PathFinder::addObstacle(const std::pair<int, int> &coordinates)
{
  obstacles.insert(coordinates);
}

void PathFinder::removeObstacle(const std::pair<int, int> &coordinates)
{
  obstacles.erase(coordinates);
}
