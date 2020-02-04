#ifndef ASSIGNMENT_ASTAR_HPP
#define ASSIGNMENT_ASTAR_HPP

#include <stack>
#include <vector>
#include "PathFinder.hpp"

class Astar : public PathFinder
{
public:
  Astar(int m, int n);
  std::list<Point>
  pathBetween(const Point &origin, const Point &destination) override;
  struct Node
  {
    int y;
    int x;
    int parentX;
    int parentY;
    float gCost;
    float hCost;
    float fCost;
  };
private:
  static void makeNodeDefault(Node &node, int i, int j);
  bool isValidPoint(Point point) const;
  Node findHighestPriorityNode(std::vector<Node> &openedNodes);
  float calculateHeuristics(int x, int y, const Node &dest) const;
  std::list<Astar::Point> calculatePath(Point dest, const std::vector<std::vector<Node>> &map);
};

#endif
