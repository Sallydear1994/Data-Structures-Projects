// expmain.cpp
//
// ICS 46 Spring 2021
// Project #1: Dark at the End of the Tunnel
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the given classes in the darkmaze library, or with your own
// algorithm implementations, outside of the context of the GUI or
// Google Test.
#include <memory>
#include "WillMaze.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "MazeFactory.hpp"
#include "MazeSolutionFactory.hpp"
#include "WillMazeSolver.hpp"

int main()
{
    std::unique_ptr<Maze> maze = MazeFactory{}.createMaze(10, 10);

    WillMaze mazegen;
    mazegen.generateMaze(*maze);

    WillMazeSolver mazegensol;

    std::unique_ptr<MazeSolution> mazesol = MazeSolutionFactory{}.createMazeSolution(*maze);
    mazegensol.solveMaze(*maze, *mazesol);

    return 0;
}

