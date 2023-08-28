#ifndef WILLMAZE_HPP
#define WILLMAZE_HPP

#include "MazeGenerator.hpp"
#include <random>

class WillMaze : public MazeGenerator
{
public:
    WillMaze();
    ~WillMaze();
    void generateMaze(Maze& maze) override;
    void choosePath(Maze& maze, std::pair<unsigned int, unsigned int> cell);
    std::vector<std::pair<unsigned int, unsigned int>> getUnvisitedNeighbors(Maze& maze, std::pair<unsigned int, unsigned int> cell);
    bool hasUnvisitedNeighbors(Maze& maze, std::pair<unsigned int, unsigned int> cell);
    bool checkCell(std::pair<unsigned int, unsigned int> cell);
    bool checkUp();
    bool checkDown();
    bool checkLeft();
    bool checkRight();

    void goUp(Maze& maze);
    void goDown(Maze& maze);
    void goLeft(Maze& maze);
    void goRight(Maze& maze);

private:
    unsigned int width;
    unsigned int height;
    unsigned int cell_x_coord;
    unsigned int cell_y_coord;
    std::random_device rd;
    std::vector<std::pair<unsigned int, unsigned int>> visited;
};

#endif // WILLMAZE_HPP

