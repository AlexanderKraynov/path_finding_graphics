#ifndef ASSIGNMENT_ASTAR_HPP
#define ASSIGNMENT_ASTAR_HPP

#include <stack>
#include <vector>
#include "PathFinder.hpp"

class Astar : public PathFinder
{
public:
  Astar(int m, int n);
  std::list<std::pair<int, int>> pathBetween(std::pair<int, int> origin, std::pair<int, int> destination) override;
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
  float calculateHeuristics(int x, int y, const Node &dest) const;
  friend bool operator<(const Astar::Node &lhs, const Astar::Node &rhs);
};

inline bool operator<(const Astar::Node &lhs, const Astar::Node &rhs);


#endif
