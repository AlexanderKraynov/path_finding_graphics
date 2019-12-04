#include "Grid.hpp"
#include <utility>
#include <iostream>

#define TEXT_MARGIN 10
#define FONT_SIZE 24

void Grid::draw(sf::RenderWindow &window)
{
  //drawing grid
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      sf::RectangleShape cell;
      cell.setPosition(i * cellLength, j * cellLength);
      cell.setSize(sf::Vector2f(cellLength, cellLength));
      cell.setOutlineThickness(1);
      cell.setFillColor(sf::Color::White);
      cell.setOutlineColor(sf::Color::Black);
      window.draw(cell);
    }
  }
  //drawing obstacles
  for (auto obstacle : algorithm->getObstacles())
  {
    sf::RectangleShape cell;
    cell.setPosition(obstacle.first * cellLength, obstacle.second * cellLength);
    cell.setSize(sf::Vector2f(cellLength, cellLength));
    cell.setOutlineThickness(1);
    cell.setFillColor(sf::Color(128, 128, 128));
    cell.setOutlineColor(sf::Color::Black);
    window.draw(cell);
  }
  //drawing origin
  sf::CircleShape begin;
  begin.setPosition(origin.first * cellLength, origin.second * cellLength);
  begin.setRadius(cellLength / 2.02);
  begin.setFillColor(sf::Color::Green);
  window.draw(begin);
  //drawing destination
  sf::CircleShape end;
  end.setPosition(destination.first * cellLength, destination.second * cellLength);
  end.setRadius(cellLength / 2.02);
  end.setFillColor(sf::Color::Red);
  window.draw(end);
  //drawing path
  if (showPath)
  {
    auto path = algorithm->pathBetween({origin.second, origin.first}, {destination.second, destination.first});
    sf::Vertex pathGraph[path.size()];
    auto it = path.begin();
    for (size_t i = 0; i < path.size(); i++)
    {
      pathGraph[i] = sf::Vertex(
        sf::Vector2f(it->first * cellLength + cellLength / 2, it->second * cellLength + cellLength / 2));
      pathGraph[i].color = sf::Color::Blue;
      it++;
    }
    window.draw(pathGraph, path.size(), sf::LineStrip);
  }
  //draw text
  sf::Font font;
  if (!font.loadFromFile("../OpenSans-Regular.ttf"))
  {
    throw std::logic_error("Font file not found");
  }
  sf::Text man;
  man.setFont(font);
  man.setPosition(TEXT_MARGIN, columns * cellLength + TEXT_MARGIN);
  man.setCharacterSize(FONT_SIZE);
  man.setFillColor(sf::Color::White);
  man.setString(
    "Press \n1 to enter obstacle placement mode (lmb to place, rmb to delete obstacle)\n2 to enter origin placement mode\n3 to enter destination placement mode\nSpace to toggle path\nEsc to exit");
  window.draw(man);
  //draw state markers
  int top_margin;
  switch (placementState)
  {
    case state::obstacles:
    {
      top_margin = 2;
      break;
    }
    case state::begin:
    {
      top_margin = 3;
      break;
    }
    case state::end:
    {
      top_margin = 4;
      break;
    }
  }
  sf::RectangleShape stateMarker;
  stateMarker.setPosition(5,
                          columns * cellLength + TEXT_MARGIN * (top_margin - 2) + top_margin * FONT_SIZE - top_margin);
  stateMarker.setSize(sf::Vector2f(FONT_SIZE, FONT_SIZE));
  stateMarker.setOutlineThickness(1);
  stateMarker.setFillColor(sf::Color::Transparent);
  stateMarker.setOutlineColor(sf::Color::White);
  window.draw(stateMarker);
}

Grid::Grid(int M, int N, int cellLength, std::shared_ptr<PathFinder> algorithm) :
  rows(M),
  columns(N),
  cellLength(cellLength),
  algorithm(std::move(algorithm)),
  origin({0, 0}),
  destination({M - 1, N - 1}),
  placementState(state::obstacles),
  showPath(false)
{
}

void Grid::addObstacle(std::pair<int, int> obstacle)
{
  algorithm->addObstacle(obstacle);
}

int Grid::getCellLength()
{
  return cellLength;
}

void Grid::removeObstacle(std::pair<int, int> obstacle)
{
  algorithm->removeObstacle(obstacle);
}

int Grid::getRows()
{
  return rows;
}

int Grid::getColumns()
{
  return columns;
}

bool Grid::isObstacle(std::pair<int, int> coordinates)
{
  return algorithm->isObstacle(coordinates);
}
