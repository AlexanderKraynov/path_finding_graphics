#include <limits>
#include <stack>
#include "Dfs.hpp"

std::list<std::pair<int, int>> Dfs::pathBetween(std::pair<int, int> origin, std::pair<int, int> destination)
{
  std::stack<std::pair<int, int>> route;
  std::unordered_set<std::pair<int, int>, pair_hash> visitedNodes;
  std::pair<int, int> currentNode = {origin.second, origin.first};
  visitedNodes.insert(currentNode);
  while (currentNode != std::pair<int, int>({destination.second, destination.first}))
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
        std::pair<int, int> node = {newX, newY};
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
  std::list<std::pair<int, int>> result;
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
