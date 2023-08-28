#include <ics46/factory/DynamicFactory.hpp>
#include "WillAI.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(
    OthelloAI, wbarsalo::WillAI, 
    "Will's AI");


wbarsalo::WillAI::WillAI()
{
    maxValue = -100;
    minValue = 100;
    currentValue = 0;
    x_coord = 0;
    y_coord = 0;
    width = 0;
    height = 0;
    valueAppears = 0;
    aiPlayerTurn = 0;
    maxDepth = 0;
    std::vector<std::pair<int, std::pair<int, int>>> priorityCoords;
    std::vector<std::pair<int, int>> chooseCoords;
}


wbarsalo::WillAI::~WillAI()
{

}


std::pair<int, int> wbarsalo::WillAI::chooseMove(const OthelloGameState& state)
{
    aiPlayerTurn = 1;
    maxDepth = 3;
    width = state.board().width();
    height = state.board().height();
    initialMoves(*state.clone());
    x_coord = priorityCoords[0].second.first;
    y_coord = priorityCoords[0].second.second;
    int value = search(*state.clone(), maxDepth);
    for (int i = 0; i < priorityCoords.size(); i++)
    {
        if (priorityCoords[i].first == value)
        {
            valueAppears += 1;
            x_coord = priorityCoords[i].second.first;
            y_coord = priorityCoords[i].second.second;
            chooseCoords.push_back(std::make_pair(priorityCoords[i].second.first, priorityCoords[i].second.second));
        }
        if (valueAppears > 1)
        {
            int index = rd() % chooseCoords.size();
            return std::make_pair(chooseCoords[index].first, chooseCoords[index].second);
        }
    }
    return std::make_pair(x_coord, y_coord);
}


void wbarsalo::WillAI::initialMoves(OthelloGameState& s)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (s.isValidMove(i, j))
            {
                if (s.isBlackTurn())
                {
                    priorityCoords.push_back(std::make_pair(s.blackScore() - s.whiteScore(), std::make_pair(i, j)));
                }
                else
                {
                    priorityCoords.push_back(std::make_pair(s.whiteScore() - s.blackScore(), std::make_pair(i, j)));
                }
            }
        }
    }
}


int wbarsalo::WillAI::evaluate(OthelloGameState& s)
{
    if (s.isWhiteTurn())
    {
        return s.whiteScore() - s.blackScore();
    }
    else
    {
        return s.whiteScore() - s.blackScore();
    }
}


int wbarsalo::WillAI::search(OthelloGameState& s, int depth)
{
    if (depth == 0)
    {
        return evaluate(s);
    }
    else
    {
        if (aiPlayerTurn == 1)
        {
            int max = -100;
            std::vector<std::pair<int, int>> moves = getValidMoves(s);
            for (int i = 0; i < moves.size(); i++)
            {
                if (depth == maxDepth)
                {
                    x_coord = moves[i].first;
                    y_coord = moves[i].second;
                }
                std::unique_ptr<OthelloGameState> sc = s.clone();
                sc->makeMove(moves[i].first, moves[i].second);
                aiPlayerTurn = 0;
                currentValue = search(*sc, depth - 1);
                if (currentValue > maxValue)
                {
                    maxValue = currentValue;
                }
                if (currentValue < minValue)
                {
                    minValue = currentValue;
                }

                if (currentValue > max)
                {
                    max = currentValue;
                }

                // Corners and end game moves always take priority
                if (depth == maxDepth)
                {
                    if ((s.isBlackTurn() && maxDepth % 2 == 0) || (s.isWhiteTurn() && maxDepth % 2 == 1))
                    {
                        priorityCoords[i].first = maxValue;
                    }
                    else
                    {
                        priorityCoords[i].first = minValue;
                    }
                    if (sc->isGameOver())
                    {
                        x_coord = moves[i].first;
                        y_coord = moves[i].second;
                        priorityCoords[i].first = 10000;
                        return 10000;
                    }
                    else if ((moves[i].first == 0 && moves[i].second == 0) || (moves[i].first == width - 1 && moves[i].second == 0) || (moves[i].first == 0 && moves[i].second == height - 1) || (moves[i].first == width - 1 && moves[i].second == height - 1))
                    {
                        x_coord = moves[i].first;
                        y_coord = moves[i].second;
                        priorityCoords[i].first = 1000;
                        return 1000; 
                    }
                }
            }

            // Notes on this algorithm
            // Black always starts the game first
            // For example, if the ai is black, and it only has a depth of 1.
            // It will make a move for a valid spot which will transition
            // to whites turn. Since it can go no further, it evaluates that
            // state and returns the value of how desirable that state is for
            // White. Since the most desirable move for White is the least
            // desirable move for black, it will return minValue 
            if (depth == maxDepth)
            {
                if ((s.isBlackTurn() && maxDepth % 2 == 0) || (s.isWhiteTurn() && maxDepth % 2 == 1))
                {
                    return maxValue;
                }
                else
                {
                    return minValue;
                }
            }
            return max;
        }
        else
        {
            int min = 1000;
            std::vector<std::pair<int, int>> moves = getValidMoves(s);
            for (int i = 0; i < moves.size(); i++)
            {
                std::unique_ptr<OthelloGameState> sc = s.clone();
                sc->makeMove(moves[i].first, moves[i].second);
                aiPlayerTurn = 1;
                currentValue = search(*sc, depth - 1);
                if (currentValue < min)
                { 
                    min = currentValue;
                }
                if (currentValue < minValue)
                {
                    minValue = currentValue;
                }
            }
            return min;
        }
    }
}


std::vector<std::pair<int, int>> wbarsalo::WillAI::getValidMoves(OthelloGameState& s)
{
    std::vector<std::pair<int, int>> moves;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (s.isValidMove(i, j))
            {
                moves.push_back(std::make_pair(i, j));
            }
        }
    }
    return moves;
}
