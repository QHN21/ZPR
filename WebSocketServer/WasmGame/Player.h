
#ifndef __PLAYER_H
#define __PLAYER_H

#include "Board.h"
#include <memory>
/**
 * Klasa odpowiedzialna za implementacje gracza i przeciwnika
 */
class Player {
private:
    std::shared_ptr<Board> board;
    int position[2];

public:
    Player(std::shared_ptr<Board> board, int x, int y) {
        position[0] = x;
        position[1] = y;
        this->board = board;
        board->getSquares()[(x * 7)+y]->setFree(false);
    }

    ~Player(){}

    bool move(int x, int y);

    bool hideSquare(int x, int y);

    bool checkMove(int x, int y);

    vector<int *> possibleMoves();

    int *getPosition();

	void reset(int x, int y);
};


#endif //UNTITLED_PLAYER_H
