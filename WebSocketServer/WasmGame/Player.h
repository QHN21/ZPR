//
// Created by Krzysztof Bednarski on 28.03.2019.
//

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include "Board.h"

/**
 * Klasa odpowiedzialna za implementacje gracza i przeciwnika
 */
class Player {
private:
    Board *board;
    int position[];

public:
    Player(Board *board, int x, int y) {
        position[0] = x;
        position[1] = y;
        this->board = board;
        board->getSquares()[(x * 7)+y]->setFree(false);
    }

    bool move(int x, int y);

    bool hideSquare(int x, int y);

    bool checkMove(int x, int y);

    vector<int *> possibleMoves();

    int *getPosition();

	void reset(int x, int y);
};


#endif //UNTITLED_PLAYER_H
