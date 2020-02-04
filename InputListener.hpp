#ifndef ASSIGNMENT_INPUTLISTENER_HPP
#define ASSIGNMENT_INPUTLISTENER_HPP

#include <functional>
#include "Grid.hpp"

class InputListener
{
public:
  static void listen(Grid &grid, sf::RenderWindow &window);
private:
  static void snapPointToMouse(Grid &grid, sf::RenderWindow &window, PathFinder::Point &point);
};


#endif
