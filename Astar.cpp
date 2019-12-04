#include "Astar.hpp"
#include <cmath>
#include <cfloat>

float Astar::calculateHeuristics(int x, int y, const Node &dest) const
{
  float H = (sqrt((x - dest.x) * (x - dest.x) + (y - dest.y) * (y - dest.y)));
  return H;
}

bool operator<(const Astar::Node &lhs, const Astar::Node &rhs)
{
  return lhs.fCost < rhs.fCost;
}

std::list<std::pair<int, int>>
Astar::pathBetween(const std::pair<int, int> origin, const std::pair<int, int> destintation)
{
  Node begin = {origin.first, origin.second};
  Node end = {destintation.first, destintation.second};
  if (obstacles.find({begin.x, begin.y}) != obstacles.end())
  {
    throw std::invalid_argument("origin is an obstacle");
  }
  if (obstacles.find({end.x, end.y}) != obstacles.end())
  {
    throw std::invalid_argument("destination is an obstacle");
  }
  bool closedNodes[rows][columns];
  Node map[rows][columns];
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      map[i][j].fCost = FLT_MAX;
      map[i][j].hCost = FLT_MAX;
      map[i][j].gCost = FLT_MAX;
      map[i][j].parentX = -1;
      map[i][j].parentY = -1;
      map[i][j].x = i;
      map[i][j].y = j;
      closedNodes[i][j] = false;
    }
  }
  int x = begin.x;
  int y = begin.y;
  map[x][y].fCost = 0.0;
  map[x][y].hCost = 0.0;
  map[x][y].gCost = 0.0;
  map[x][y].parentX = x;
  map[x][y].parentY = y;
  std::vector<Node> openedNodes;
  openedNodes.emplace_back(map[x][y]);

  while (!openedNodes.empty() && openedNodes.size() < rows * columns)
  {
    Node node{};
    do
    {
      float min = FLT_MAX;
      std::vector<Node>::iterator itNode;
      for (auto it = openedNodes.begin(); it != openedNodes.end(); it = next(it))
      {
        Node n = *it;
        if (n.fCost < min)
        {
          min = n.fCost;
          itNode = it;
        }
      }
      node = *itNode;
      openedNodes.erase(itNode);
    } while (obstacles.find({node.x, node.y}) != obstacles.end());
    x = node.x;
    y = node.y;
    closedNodes[x][y] = true;
    for (int i = -1; i <= 1; i++)
    {
      for (int j = -1; j <= 1; j++)
      {
        if (i * j != 0)
        {
          continue;
        }
        int newX = x + i;
        int newY = y + j;
        float gValue, fValue, hValue;
        if (obstacles.find({newX, newY}) == obstacles.end() && (newX >= 0) && (newX < rows) && newY >= 0 &&
            newY < columns)
        {
          if (newX == end.x && newY == end.y)
          {
            map[newX][newY].parentX = x;
            map[newX][newY].parentY = y;
            int destx = end.x;
            int desty = end.y;
            std::stack<Node> path;
            std::list<std::pair<int, int>> result;
            while (!(map[destx][desty].parentX == destx && map[destx][desty].parentY == desty)
                   && map[destx][desty].x != -1 && map[destx][desty].y != -1)
            {
              path.push(map[destx][desty]);
              int tempX = map[destx][desty].parentX;
              int tempY = map[destx][desty].parentY;
              destx = tempX;
              desty = tempY;
            }
            path.push(map[destx][desty]);
            while (!path.empty())
            {
              Node top = path.top();
              path.pop();
              result.emplace_back(top.x, top.y);
            }
            return result;
          }
          else if (!closedNodes[newX][newY])
          {
            gValue = node.gCost + (i == j ? 1.414 : 1.0);
            hValue = calculateHeuristics(newX, newY, end);
            fValue = gValue + hValue;
            if (map[newX][newY].fCost == FLT_MAX || map[newX][newY].fCost > fValue)
            {
              map[newX][newY].fCost = fValue;
              map[newX][newY].gCost = gValue;
              map[newX][newY].hCost = hValue;
              map[newX][newY].parentX = x;
              map[newX][newY].parentY = y;
              openedNodes.emplace_back(map[newX][newY]);
            }
          }
        }
      }
    }

  }

  return std::list<std::pair<int, int>>();
}

Astar::Astar(int m, int n) : PathFinder(m, n)
{

}


