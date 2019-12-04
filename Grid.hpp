#ifndef ASSIGNMENT_GRID_HPP
#define ASSIGNMENT_GRID_HPP


#include <SFML/Graphics.hpp>
#include <memory>
#include "PathFinder.hpp"

class InputListener;

class Grid
{
public:
  Grid(int M, int N, int length, std::shared_ptr<PathFinder> algorithm);
  void draw(sf::RenderWindow&);
  void addObstacle(std::pair<int,int> obstacle);
  void removeObstacle(std::pair<int,int> obstacle);
  bool isObstacle(std::pair<int,int> coordinates);
  int getCellLength();
  int getRows();
  int getColumns();
  enum state
  {
    obstacles,
    begin,
    end
  };

  std::pair<int,int> origin;
  std::pair<int,int> destination;
  bool showPath;

private:
  int rows;
  int columns;
  int cellLength;
  state placementState;
  std::shared_ptr<PathFinder> algorithm;
  friend InputListener;
};

#endif
