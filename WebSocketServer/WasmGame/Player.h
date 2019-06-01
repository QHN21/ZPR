//
// Created by Krzysztof Bednarski on 28.03.2019.
//

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

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

    ~Player(){
      //delete this -> board;
      std::cout<<"Player Destroyed"<<std::endl;
    }

    bool move(int x, int y);

    bool hideSquare(int x, int y);

    bool checkMove(int x, int y);

    vector<int *> possibleMoves();

    int *getPosition();

	void reset(int x, int y);
};


#endif //UNTITLED_PLAYER_H
