#include "Astar.hpp"
#include <cmath>
#include <cfloat>
#include <exception>

float Astar::calculateHeuristics(int x, int y, const Node &dest) const
{
  float H = (sqrt((x - dest.x) * (x - dest.x) + (y - dest.y) * (y - dest.y)));
  return H;
}

std::list<Astar::Point>
Astar::pathBetween(const Point &origin, const Point &destintation)
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
  std::vector<std::vector<Node> > map(rows, std::vector<Node> (columns));
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      makeNodeDefault(map[i][j], i, j);
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
    Node node = findHighestPriorityNode(openedNodes);
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
        if (isValidPoint({newX, newY}))
        {
          if (newX == end.x && newY == end.y)
          {
            map[newX][newY].parentX = x;
            map[newX][newY].parentY = y;
            int destx = end.x;
            int desty = end.y;
            return std::move(calculatePath({destx, desty}, map));
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
  return std::list<Point>();
}

Astar::Astar(int m, int n) : PathFinder(m, n)
{
}

Astar::Node Astar::findHighestPriorityNode(std::vector<Node> &openedNodes)
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
  return node;
}

void Astar::makeNodeDefault(Astar::Node &node, int i, int j)
{
  node.fCost = FLT_MAX;
  node.hCost = FLT_MAX;
  node.gCost = FLT_MAX;
  node.parentX = -1;
  node.parentY = -1;
  node.x = i;
  node.y = j;
}

bool Astar::isValidPoint(PathFinder::Point point) const
{
  return obstacles.find(point) == obstacles.end() && (point.first >= 0) && (point.first < rows) && point.second >= 0 &&
         point.second < columns;
}

std::list<Astar::Point> Astar::calculatePath(Point dest, const std::vector<std::vector<Node>> &map)
{
  std::stack<Node> path;
  std::list<Point> result;
  int destx = dest.first;
  int desty = dest.second;
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


