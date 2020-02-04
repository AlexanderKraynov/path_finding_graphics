#include "Grid.hpp"
#include <utility>
#include <iostream>
#include "resources/strings/strings.hpp"

#define TEXT_MARGIN 10
#define FONT_SIZE 24

void Grid::draw(sf::RenderWindow &window) const
{
  drawGrid(window);
  drawObstacles(window, sf::Color(128, 128, 128));
  drawPoint(window, origin, sf::Color::Green);
  drawPoint(window, destination, sf::Color::Red);
  drawPath(window, sf::Color::Blue);
  drawUI(window, sf::Color::White);
}

Grid::Grid(int M, int N, int cellLength, const std::shared_ptr<PathFinder> &algorithm) :
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

void Grid::addObstacle(const PathFinder::Point &obstacle)
{
  algorithm->addObstacle(obstacle);
}

int Grid::getCellLength() const
{
  return cellLength;
}

void Grid::removeObstacle(const PathFinder::Point &obstacle)
{
  algorithm->removeObstacle(obstacle);
}

int Grid::getRows() const
{
  return rows;
}

int Grid::getColumns() const
{
  return columns;
}

bool Grid::isObstacle(const PathFinder::Point &coordinates) const
{
  return algorithm->isObstacle(coordinates);
}

void Grid::drawGrid(sf::RenderWindow &window, int outlineThickness) const
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      sf::RectangleShape cell;
      cell.setPosition(i * cellLength, j * cellLength);
      cell.setSize(sf::Vector2f(cellLength, cellLength));
      cell.setOutlineThickness(outlineThickness);
      cell.setFillColor(sf::Color::White);
      cell.setOutlineColor(sf::Color::Black);
      window.draw(cell);
    }
  }
}

void Grid::drawObstacles(sf::RenderWindow &window, const sf::Color &obstacleColor) const
{
  for (auto obstacle : algorithm->getObstacles())
  {
    sf::RectangleShape cell;
    cell.setPosition(obstacle.first * cellLength, obstacle.second * cellLength);
    cell.setSize(sf::Vector2f(cellLength, cellLength));
    cell.setOutlineThickness(1);
    cell.setFillColor(obstacleColor);
    cell.setOutlineColor(sf::Color::Black);
    window.draw(cell);
  }
}

void Grid::drawPoint(sf::RenderWindow &window, const PathFinder::Point &pos, const sf::Color &pointColor) const
{
  sf::CircleShape begin;
  begin.setPosition(pos.first * cellLength, pos.second * cellLength);
  begin.setRadius(cellLength / 2.02);
  begin.setFillColor(pointColor);
  window.draw(begin);
}

void Grid::drawPath(sf::RenderWindow &window, const sf::Color &pathColor) const
{
  if (showPath)
  {
    auto path = algorithm->pathBetween({origin.second, origin.first}, {destination.second, destination.first});
    sf::Vertex pathGraph[path.size()];
    auto it = path.begin();
    for (size_t i = 0; i < path.size(); i++)
    {
      pathGraph[i] = sf::Vertex(
        sf::Vector2f(it->first * cellLength + cellLength / 2, it->second * cellLength + cellLength / 2));
      pathGraph[i].color = pathColor;
      it++;
    }
    window.draw(pathGraph, path.size(), sf::LineStrip);
  }
}

void Grid::drawUI(sf::RenderWindow &window, const sf::Color &textColor) const
{
  sf::Font font;
  if (!font.loadFromFile(openSansPath))
  {
    throw std::logic_error("Font file not found");
  }
  sf::Text man;
  man.setFont(font);
  man.setPosition(TEXT_MARGIN, columns * cellLength + TEXT_MARGIN);
  man.setCharacterSize(FONT_SIZE);
  man.setFillColor(textColor);
  man.setString(uiText);
  window.draw(man);
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
    default:
    {
      throw std::runtime_error("Invalid grid state. Undefinded behaviour possible");
    }
  }
  sf::RectangleShape stateMarker;
  stateMarker.setPosition(5,
                          columns * cellLength + TEXT_MARGIN * (top_margin - 2) + top_margin * FONT_SIZE - top_margin);
  stateMarker.setSize(sf::Vector2f(FONT_SIZE, FONT_SIZE));
  stateMarker.setOutlineThickness(1);
  stateMarker.setFillColor(sf::Color::Transparent);
  stateMarker.setOutlineColor(textColor);
  window.draw(stateMarker);
}

