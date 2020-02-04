#ifndef ASSIGNMENT_GRID_HPP
#define ASSIGNMENT_GRID_HPP


#include <SFML/Graphics.hpp>
#include <memory>
#include "PF/PathFinder.hpp"

class InputListener;

class Grid
{
public:
  Grid(int M, int N, int length, const std::shared_ptr<PathFinder> &algorithm);
  void draw(sf::RenderWindow &) const;
  void addObstacle(const PathFinder::Point &obstacle);
  void removeObstacle(const PathFinder::Point &obstacle);
  bool isObstacle(const PathFinder::Point &coordinates) const;
  int getCellLength() const;
  int getRows() const;
  int getColumns() const;
  enum state
  {
    obstacles,
    begin,
    end
  };

  PathFinder::Point origin;
  PathFinder::Point destination;
  bool showPath;

private:
  void drawGrid(sf::RenderWindow &window, int outlineThickness = 1) const;
  void drawObstacles(sf::RenderWindow &window, const sf::Color &obstacleColor) const;
  void drawPoint(sf::RenderWindow &window, const PathFinder::Point &pos, const sf::Color &pointColor) const;
  void drawPath(sf::RenderWindow &window, const sf::Color &pathColor) const;
  void drawUI(sf::RenderWindow &window, const sf::Color &textColor) const;
  int rows;
  int columns;
  int cellLength;
  state placementState;
  std::shared_ptr<PathFinder> algorithm;
  friend InputListener;
};

#endif
