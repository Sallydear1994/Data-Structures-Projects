
#ifndef WILLMAZESOLVER_HPP
#define WILLMAZESOLVER_HPP

#include "MazeSolver.hpp"
#include <vector>

class WillMazeSolver : public MazeSolver
{
public:
    WillMazeSolver();
    ~WillMazeSolver();
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
    void startPath(const Maze& maze, MazeSolution& mazeSolution);
    void goInitialDirection(const Maze& maze, MazeSolution& mazeSolution);
    void chooseNextDirection(const Maze& maze, MazeSolution& mazeSolution);
    void backTrack(const Maze& maze, MazeSolution& mazeSolution);
    void choosePath(const Maze& maze, MazeSolution& mazeSolution);
    void checkUpDirections(const Maze& maze, MazeSolution& mazeSolution);
    void checkDownDirections(const Maze& maze, MazeSolution& mazeSolution);
    void checkLeftDirections(const Maze& maze, MazeSolution& mazeSolution);
    void checkRightDirections(const Maze& maze, MazeSolution& mazeSolution);
    
    std::pair<unsigned int, unsigned int> getPath(const Maze& maze, MazeSolution& mazeSolution);
    void goLeftOrRight(const Maze& maze, MazeSolution& mazeSolution);
    void goDownOrLeft(const Maze& maze, MazeSolution& mazeSolution);
    void goDownOrRight(const Maze& maze, MazeSolution& mazeSolution);
    void goUpOrLeft(const Maze& maze, MazeSolution& mazeSolution);
    void goUpOrRight(const Maze& maze, MazeSolution& mazeSolution);
    void goDownOrUp(const Maze& maze, MazeSolution& mazeSolution);
    bool checkCell(std::pair<unsigned int, unsigned int> cell);

    void goLeftUpOrRight(const Maze& maze, MazeSolution& mazeSolution);
    void goUpRightOrDown(const Maze& maze, MazeSolution& mazeSolution);
    void goLeftDowntOrRight(const Maze& maze, MazeSolution& mazeSolution);
    void goUpLeftOrDown(const Maze& maze, MazeSolution& mazeSolution);

private:
    unsigned int width;
    unsigned int height;
    unsigned int curr_path_x_coord;
    unsigned int curr_path_y_coord;
    unsigned int end_path_x_coord;
    unsigned int end_path_y_coord;
    std::vector<std::pair<unsigned int, unsigned int>> visited;
};
#endif // WILLMAZESOLVER_HPP

