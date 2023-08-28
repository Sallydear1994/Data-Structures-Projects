#include "WillMaze.hpp"
#include "Maze.hpp"
#include "ics46/factory/DynamicFactory.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, WillMaze, "Will's MazeGenerator (Required)");

WillMaze::WillMaze()
{
    width = 0;
    height = 0;
    cell_x_coord = 0;
    cell_y_coord = 0;
    std::vector<std::pair<unsigned int, unsigned int>> visited;
}

WillMaze::~WillMaze()
{
}

void WillMaze::generateMaze(Maze& maze)
{
    width = maze.getWidth();
    height = maze.getHeight();
    maze.addAllWalls();
    choosePath(maze, std::make_pair(cell_x_coord, cell_y_coord));
}
void WillMaze::choosePath(Maze& maze, std::pair<unsigned int, unsigned int> cell)
{
    visited.push_back(cell);
    while (hasUnvisitedNeighbors(maze, cell))
    {
        std::vector<std::pair<unsigned int, unsigned int>> unvisitedneighbors = getUnvisitedNeighbors(maze, cell);
        int neighbor_index = rd() % unvisitedneighbors.size();
        if (cell_y_coord > unvisitedneighbors[neighbor_index].second)
            goUp(maze);
        else if (cell_y_coord < unvisitedneighbors[neighbor_index].second)
            goDown(maze);
        else if (cell_x_coord > unvisitedneighbors[neighbor_index].first)
            goLeft(maze);
        else
            goRight(maze);
        choosePath(maze, std::make_pair(cell_x_coord, cell_y_coord));
    }
}

bool WillMaze::hasUnvisitedNeighbors(Maze& maze, std::pair<unsigned int, unsigned int> cell)
{
    if (!getUnvisitedNeighbors(maze, cell).empty())
        return true;
    return false;
}

std::vector<std::pair<unsigned int, unsigned int>> WillMaze::getUnvisitedNeighbors(Maze& maze, std::pair<unsigned int, unsigned int> cell)
{
    cell_x_coord = cell.first;
    cell_y_coord = cell.second;
    std::vector<std::pair<unsigned int, unsigned int>> neighbors; 
    if (checkUp())
        neighbors.push_back(std::make_pair(cell_x_coord, cell_y_coord - 1));
    if (checkDown())
        neighbors.push_back(std::make_pair(cell_x_coord, cell_y_coord + 1));
    if (checkLeft())
        neighbors.push_back(std::make_pair(cell_x_coord - 1, cell_y_coord));
    if (checkRight())
        neighbors.push_back(std::make_pair(cell_x_coord + 1, cell_y_coord));
    return neighbors;
}


bool WillMaze::checkCell(std::pair<unsigned int, unsigned int> cell)
{
    for (unsigned int i = 0; i < visited.size(); i++)
    {
        if (cell == visited[i])
            return false;
    }
    return true;
}

bool WillMaze::checkUp()
{
    if (cell_y_coord > 0)
    {
        if (checkCell(std::make_pair(cell_x_coord, cell_y_coord - 1)))
            return true;
    }
    return false;
}

bool WillMaze::checkDown()
{
    if (cell_y_coord < height - 1)
    {
        if (checkCell(std::make_pair(cell_x_coord, cell_y_coord + 1)))
            return true;
    }
    return false;
}

bool WillMaze::checkLeft()
{
    if (cell_x_coord > 0)
    {
        if (checkCell(std::make_pair(cell_x_coord - 1, cell_y_coord)))
            return true;
    }
    return false; 
}

bool WillMaze::checkRight()
{
    if (cell_x_coord < width - 1)
    {
        if (checkCell(std::make_pair(cell_x_coord + 1, cell_y_coord)))
            return true;
    }
    return false;
}

void WillMaze::goUp(Maze& maze)
{
    maze.removeWall(cell_x_coord, cell_y_coord, Direction::up);
    cell_y_coord -= 1;
}
void WillMaze::goDown(Maze& maze)
{
    maze.removeWall(cell_x_coord, cell_y_coord, Direction::down);
    cell_y_coord += 1;
}

void WillMaze::goLeft(Maze& maze)
{
    maze.removeWall(cell_x_coord, cell_y_coord, Direction::left);
    cell_x_coord -= 1;
}

void WillMaze::goRight(Maze& maze)
{
    maze.removeWall(cell_x_coord, cell_y_coord, Direction::right);
    cell_x_coord += 1;
}
