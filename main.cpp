#include <iostream>
#include "PF/Astar.hpp"
#include "PF/Dfs.hpp"
#include "Grid.hpp"
#include "InputListener.hpp"

#define WINDOW_HEIGHT 1080
#define WINDOW_WIDTH 1920
#define CELL_WIDTH 50

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 4)
    {
      throw std::invalid_argument("3 arguments required");
    }
    const int GRID_WIDTH = std::stoi(argv[1]);
    const int GRID_HEIGHT = std::stoi(argv[2]);
    if (GRID_WIDTH > 38 || GRID_WIDTH <= 0 || GRID_HEIGHT > 15 || GRID_HEIGHT <= 0)
    {
      throw std::invalid_argument("error: grid width is [1,38], grid height is [1,15]");
    }
    std::string arg3 = argv[3];
    if (arg3 != "astar" && arg3 != "dfs")
    {
      throw std::invalid_argument(R"(error: argument 3 should be "astar" or "dfs")");
    }
    sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pathfinding", sf::Style::Close);
    std::shared_ptr<PathFinder> pathFinderPtr;
    if (arg3 == "astar")
    {
      pathFinderPtr.reset(new Astar(GRID_WIDTH, GRID_HEIGHT));
    }
    else
    {
      pathFinderPtr.reset(new Dfs(GRID_WIDTH, GRID_HEIGHT));
    }
    Grid grid(GRID_WIDTH, GRID_HEIGHT, CELL_WIDTH, pathFinderPtr);
    while (mainWindow.isOpen())
    {
      InputListener::listen(grid, mainWindow);
      grid.draw(mainWindow);
      mainWindow.display();
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}