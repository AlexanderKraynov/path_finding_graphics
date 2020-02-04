#include <limits>
#include <stack>
#include "Dfs.hpp"

std::list<Dfs::Point> Dfs::pathBetween(const Point &origin, const Point &destination)
{
  std::stack<Point> route;
  std::unordered_set<Point, pair_hash> visitedNodes;
  Point currentNode = {origin.second, origin.first};
  visitedNodes.insert(currentNode);
  while (currentNode != Point({destination.second, destination.first}))
  {
    bool foundNotVisited = false;
    for (int i = -1; i <= 1; i++)
    {
      for (int j = -1; j <= 1; j++)
      {
        if ((i * j != 0))
        {
          continue;
        }
        int newX = currentNode.first + i;
        int newY = currentNode.second + j;
        Point node = {newX, newY};
        if (!((newX >= 0) && (newX < rows) && newY >= 0 && newY < columns) || obstacles.find(node) != obstacles.end())
        {
          continue;
        }

        if (visitedNodes.find(node) == visitedNodes.end())
        {
          route.push(currentNode);
          visitedNodes.insert(node);
          currentNode = node;
          foundNotVisited = true;
          goto mit;
        }
      }
    }
    mit:
    if (foundNotVisited)
    {
      continue;
    }
    if (route.empty())
    {
      break;
    }
    currentNode = route.top();
    route.pop();
  }
  route.push({destination.second, destination.first});
  std::list<Point> result;
  while (!route.empty())
  {
    result.push_back(route.top());
    route.pop();
  }
  return result;
}

Dfs::Dfs(int rows, int columns) : PathFinder(rows, columns)
{
}
