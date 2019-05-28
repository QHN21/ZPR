//
// Created by Krzysztof Bednarski on 28.03.2019.
//

#ifndef UNTITLED_AI_H
#define UNTITLED_AI_H

#include "Player.h"

/**
 * Klasa AI odpowiedzialna za implementacje sztucznej inteligencji.
 */
class AI {
private:
  Board* board;
public:
    AI(Board* board) {
      this -> board = board;
    }

    int *minmax(int *positionO, int *positionP, int depth, int alpha, int beta, vector<int *> freeSquares);

    int minmax_leaves(int *positionO, int *positionP, int depth, int alpha, int beta, bool maximize,
                      vector<int *> freeSquares);

    int checkPoints(int position[], vector<int *> freeSquares);

    vector<int *> possibleMoves(int *position, vector<int *> board);
};


#endif //UNTITLED_AI_H
