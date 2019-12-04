#include "InputListener.hpp"

void InputListener::listen(Grid &grid, sf::RenderWindow &window)
{
  sf::Event event{};
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      window.close();
    if (event.type == event.KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Space)
      {
        grid.showPath = !grid.showPath;
      }
      if (event.key.code == sf::Keyboard::Escape)
      {
        window.close();
      }
    }
  }
  window.clear();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
  {
    grid.placementState = Grid::state::obstacles;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
  {
    grid.placementState = Grid::state::begin;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
  {
    grid.placementState = Grid::state::end;
  }
  switch (grid.placementState)
  {
    case (Grid::state::obstacles):
    {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        int mousePositionX = sf::Mouse::getPosition(window).x / grid.getCellLength();
        int mousePositionY = sf::Mouse::getPosition(window).y / grid.getCellLength();
        if (!((grid.destination.first == mousePositionX && grid.destination.second == mousePositionY) ||
              (grid.origin.first == mousePositionX && grid.origin.second == mousePositionY)) &&
            (mousePositionX < grid.getRows()) && mousePositionY < grid.getColumns() && mousePositionX >= 0 &&
            mousePositionY >= 0)
        {
          grid.addObstacle({mousePositionX, mousePositionY});
        }
      }
      if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
      {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        grid.removeObstacle({mousePosition.x / grid.getCellLength(), mousePosition.y / grid.getCellLength()});
      }
      break;
    }
    case (Grid::state::begin):
    {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        int mousePositionX = mousePosition.x / grid.getCellLength();
        int mousePositionY = mousePosition.y / grid.getCellLength();
        if (!grid.isObstacle({mousePositionX, mousePositionY}) &&
            (((mousePositionX < grid.getRows()) && mousePositionY < grid.getColumns() && mousePositionX >= 0 &&
              mousePositionY >= 0)) &&
            !((grid.destination.first == mousePositionX && grid.destination.second == mousePositionY)))
        {
          grid.origin.first = mousePosition.x / grid.getCellLength();
          grid.origin.second = mousePosition.y / grid.getCellLength();
        }
      }
      break;
    }
    case (Grid::state::end):
    {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        int mousePositionX = mousePosition.x / grid.getCellLength();
        int mousePositionY = mousePosition.y / grid.getCellLength();
        if (!grid.isObstacle({mousePositionX, mousePositionY}) &&
            (((mousePositionX < grid.getRows()) && mousePositionY < grid.getColumns() && mousePositionX >= 0 &&
              mousePositionY >= 0)) &&
            !((grid.origin.first == mousePositionX && grid.origin.second == mousePositionY)))
        {
          grid.destination.first = mousePosition.x / grid.getCellLength();
          grid.destination.second = mousePosition.y / grid.getCellLength();
        }
      }
      break;
    }
  }
}
