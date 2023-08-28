#include "WillMazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "ics46/factory/DynamicFactory.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, WillMazeSolver, "Will's MazeSolver (Required)");

WillMazeSolver::WillMazeSolver()
{
    width = 0;
    height = 0;
    curr_path_x_coord = 0;
    curr_path_y_coord = 0;
    end_path_x_coord = 0;
    end_path_y_coord = 0;
    std::vector<std::pair<unsigned int, unsigned int>> visited;
}
WillMazeSolver::~WillMazeSolver()
{
    
}
void WillMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    width = mazeSolution.getWidth();
    height = mazeSolution.getHeight();
    end_path_x_coord = mazeSolution.getEndingCell().first;
    end_path_y_coord = mazeSolution.getEndingCell().second;
    startPath(maze, mazeSolution);
}

void WillMazeSolver::startPath(const Maze& maze, MazeSolution& mazeSolution)
{
    curr_path_x_coord = mazeSolution.getStartingCell().first;
    curr_path_y_coord = mazeSolution.getStartingCell().second;
    goInitialDirection(maze, mazeSolution);
    visited.push_back(mazeSolution.getStartingCell());
    choosePath(maze, mazeSolution);
}

// This is here in case the start coord and the end coords are not (0,0) and (width - 1, height - 1)
void WillMazeSolver::goInitialDirection(const Maze& maze, MazeSolution& mazeSolution)
{
    if ((end_path_y_coord > curr_path_y_coord) && (end_path_x_coord >= curr_path_x_coord))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
            mazeSolution.extend(Direction::down);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
            mazeSolution.extend(Direction::right);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
            mazeSolution.extend(Direction::left);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
            mazeSolution.extend(Direction::up);
    }

    else if ((end_path_y_coord > curr_path_y_coord) && (end_path_x_coord < curr_path_x_coord))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
            mazeSolution.extend(Direction::down);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
            mazeSolution.extend(Direction::left);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
            mazeSolution.extend(Direction::right);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
            mazeSolution.extend(Direction::up);
    }
    
    else if ((end_path_y_coord == curr_path_y_coord) && (end_path_x_coord >= curr_path_x_coord))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
            mazeSolution.extend(Direction::right);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
            mazeSolution.extend(Direction::left);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
            mazeSolution.extend(Direction::down);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
            mazeSolution.extend(Direction::up);
    }

    else if ((end_path_y_coord == curr_path_y_coord) && (end_path_x_coord < curr_path_x_coord))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
            mazeSolution.extend(Direction::left);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
            mazeSolution.extend(Direction::right);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
            mazeSolution.extend(Direction::down);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
            mazeSolution.extend(Direction::up);
    }
    else if ((end_path_y_coord < curr_path_y_coord) && (end_path_x_coord >= curr_path_x_coord))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
            mazeSolution.extend(Direction::up);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
            mazeSolution.extend(Direction::right);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
            mazeSolution.extend(Direction::left);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
            mazeSolution.extend(Direction::down);
    }
    else if ((end_path_y_coord < curr_path_y_coord) && (end_path_x_coord < curr_path_x_coord))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
            mazeSolution.extend(Direction::up);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
            mazeSolution.extend(Direction::left);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
            mazeSolution.extend(Direction::right);
        else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
            mazeSolution.extend(Direction::down);
    }
}

void WillMazeSolver::goLeftOrRight(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (end_path_x_coord >= curr_path_x_coord)
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::right);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::left);
        }
    }
}
void WillMazeSolver::goDownOrLeft(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
    {
        if (end_path_y_coord >= curr_path_y_coord)
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::down);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::left);
        }
    }
}
void WillMazeSolver::goDownOrRight(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (end_path_y_coord >= curr_path_y_coord)
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::down);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::right);
        }
    }
}

void WillMazeSolver::goUpOrLeft(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
    {
        if (end_path_y_coord <= curr_path_y_coord)
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::up);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::left);
        }
    }
}

void WillMazeSolver::goUpOrRight(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (end_path_y_coord <= curr_path_y_coord)
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::up);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::right);
        }
    }
}

void WillMazeSolver::goDownOrUp(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
    {
        if (end_path_y_coord <= curr_path_y_coord)
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::up);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::down);
        }
    }   
}

void WillMazeSolver::goLeftUpOrRight(const Maze& maze, MazeSolution& mazeSolution)
{
    if (end_path_y_coord <= curr_path_y_coord && end_path_x_coord < curr_path_x_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::left);
    }
    else if (end_path_y_coord <= curr_path_y_coord && end_path_x_coord == curr_path_x_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::up);
    }
    else if (end_path_y_coord <= curr_path_y_coord && end_path_x_coord > curr_path_x_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::right);
    }
    else 
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::up);
    }
}

void WillMazeSolver::goUpRightOrDown(const Maze& maze, MazeSolution& mazeSolution)
{
    if (end_path_x_coord >= curr_path_x_coord && end_path_y_coord < curr_path_y_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::up);
    }
    else if (end_path_x_coord >= curr_path_x_coord && end_path_y_coord == curr_path_y_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::right);
    }
    else if (end_path_x_coord >= curr_path_x_coord && end_path_y_coord == curr_path_y_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::down);
    }
    else
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::right);
    }
}

void WillMazeSolver::goLeftDowntOrRight(const Maze& maze, MazeSolution& mazeSolution)
{
    if (end_path_y_coord >= curr_path_y_coord && end_path_x_coord < curr_path_x_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::left);
    }
    else if (end_path_y_coord >= curr_path_y_coord && end_path_x_coord == curr_path_x_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::down);
    }
    else if (end_path_y_coord >= curr_path_y_coord && end_path_x_coord > curr_path_x_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::right);
    }
    else
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::down);
    }
}

void WillMazeSolver::goUpLeftOrDown(const Maze& maze, MazeSolution& mazeSolution)
{
    if (end_path_x_coord <= curr_path_x_coord && end_path_y_coord < curr_path_y_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::up);
    }
    else if (end_path_x_coord <= curr_path_x_coord && end_path_y_coord == curr_path_y_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::left);
    }
    else if (end_path_x_coord <= curr_path_x_coord && end_path_y_coord > curr_path_y_coord)
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::down);
    }
    else
    {
        visited.push_back(mazeSolution.getCurrentCell());
        mazeSolution.extend(Direction::left);
    }
}

void WillMazeSolver::checkUpDirections(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
        {
            goLeftUpOrRight(maze, mazeSolution);
        }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::up);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::right);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::left);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
        goLeftOrRight(maze, mazeSolution);
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
        goUpOrRight(maze, mazeSolution);
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
        goUpOrLeft(maze, mazeSolution);
}

void WillMazeSolver::checkDownDirections(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
        {
            goLeftDowntOrRight(maze, mazeSolution);
        }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::down);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::right);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::left);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
        goLeftOrRight(maze, mazeSolution);
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
        goDownOrRight(maze, mazeSolution);
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
        goDownOrLeft(maze, mazeSolution);
}

void WillMazeSolver::checkLeftDirections(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
    {
        goUpLeftOrDown(maze, mazeSolution);
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::left);   
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::down);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::up);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left))
        goDownOrUp(maze, mazeSolution);
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
        goUpOrLeft(maze, mazeSolution);
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
        goDownOrLeft(maze, mazeSolution);
}
void WillMazeSolver::checkRightDirections(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right) && !maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
    {
        goUpRightOrDown(maze, mazeSolution);
    }
    if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::right);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::down);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
    {
        if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.extend(Direction::up);
        }
        else
        {
            visited.push_back(mazeSolution.getCurrentCell());
            mazeSolution.backUp();
        }
    }
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right))
        goDownOrUp(maze, mazeSolution);
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down))
        goUpOrRight(maze, mazeSolution);
    else if (maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up))
        goDownOrRight(maze, mazeSolution);
}

void WillMazeSolver::chooseNextDirection(const Maze& maze, MazeSolution& mazeSolution)
{
    curr_path_x_coord = mazeSolution.getCurrentCell().first;
    curr_path_y_coord = mazeSolution.getCurrentCell().second;
    if (checkCell(mazeSolution.getCurrentCell()))
    {
        std::vector<Direction> paths = mazeSolution.getMovements();
        if (paths[paths.size() - 1] == Direction::up)
            checkUpDirections(maze, mazeSolution);
        else if (paths[paths.size() - 1] == Direction::down)
            checkDownDirections(maze, mazeSolution);
        else if (paths[paths.size() - 1] == Direction::left)
            checkLeftDirections(maze, mazeSolution);
        else if (paths[paths.size() - 1] == Direction::right)
            checkRightDirections(maze, mazeSolution);
    }
    else
    {
        backTrack(maze, mazeSolution);
        chooseNextDirection(maze, mazeSolution);
    }
}
bool WillMazeSolver::checkCell(std::pair<unsigned int, unsigned int> cell)
{
    for (unsigned int i = 0; i < visited.size(); i++)
    {
        if (cell == visited[i])
            return false;
    }
    return true;
}

void WillMazeSolver::backTrack(const Maze& maze, MazeSolution& mazeSolution)
{
    if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::up) && checkCell(std::make_pair(curr_path_x_coord, curr_path_y_coord - 1)))
    {
        mazeSolution.extend(Direction::up);
    }
    else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::right) && checkCell(std::make_pair(curr_path_x_coord + 1, curr_path_y_coord)))
    {
        mazeSolution.extend(Direction::right);
    }
    else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::down) && checkCell(std::make_pair(curr_path_x_coord, curr_path_y_coord + 1)))
    {
        mazeSolution.extend(Direction::down);
    }
    else if (!maze.wallExists(curr_path_x_coord, curr_path_y_coord, Direction::left) && checkCell(std::make_pair(curr_path_x_coord - 1, curr_path_y_coord)))
    {
        mazeSolution.extend(Direction::left);
    }
    else
    {
        mazeSolution.backUp();
    }
}

void WillMazeSolver::choosePath(const Maze& maze, MazeSolution& mazeSolution)
{
    curr_path_x_coord = mazeSolution.getCurrentCell().first;
    curr_path_y_coord = mazeSolution.getCurrentCell().second;
    if (!mazeSolution.isComplete())
    {
        chooseNextDirection(maze, mazeSolution);
        choosePath(maze, mazeSolution);
    }
}
