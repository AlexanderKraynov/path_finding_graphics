#include "PathFinder.hpp"

std::unordered_set<std::pair<int, int>, PathFinder::pair_hash> PathFinder::getObstacles()
{
  return obstacles;
}

bool PathFinder::isObstacle(std::pair<int, int> coordinates)
{
  return obstacles.find(coordinates) != obstacles.end();
}

void PathFinder::addObstacle(std::pair<int, int> coordinates)
{
  obstacles.insert(coordinates);
}

void PathFinder::removeObstacle(std::pair<int, int> coordinates)
{
  obstacles.erase(coordinates);
}
