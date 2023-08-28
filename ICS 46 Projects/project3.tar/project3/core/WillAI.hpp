#ifndef WILLAI_HPP
#define WILLAI_HPP  

// Disqualification rules
// 1. Your code doesn't compile, or it doesn't link with everyone else's
// 2. Choose an invalid move
// 3. Throw some kind of exception or crash while choosing a move.
// 4. Take too long to make a move (3 CPU seconds, on my machine)

#include "OthelloAI.hpp"
#include <random>

namespace wbarsalo
{
    class WillAI : public OthelloAI
    {
    public:
        WillAI();
        ~WillAI();
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
        int evaluate(OthelloGameState& s);
        int search(OthelloGameState& s, int depth);
        std::vector<std::pair<int, int>> getValidMoves(OthelloGameState& s);
        void initialMoves(OthelloGameState& s);
    private:
        int maxValue;
        int minValue;
        int currentValue;
        int x_coord;
        int y_coord;
        int width;
        int height;
        int valueAppears;
        int aiPlayerTurn;
        int maxDepth;

        std::random_device rd;
        std::vector<std::pair<int, std::pair<int, int>>> priorityCoords;
        std::vector<std::pair<int, int>> chooseCoords;
    };
}

#endif // WILLAI_HPP  
