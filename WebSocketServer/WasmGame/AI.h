
#ifndef __AI_H
#define __AI_H

#include "Player.h"

/**
 * Klasa AI odpowiedzialna za implementacje sztucznej inteligencji.
 */
class AI {
private:
  std::shared_ptr<Board> board;
public:
    AI(std::shared_ptr<Board> board) {
      this -> board = board;
    }

    ~AI(){}

    int *minmax(int *positionO, int *positionP, int depth, int alpha, int beta, vector<int *> freeSquares);

    int minmax_leaves(int *positionO, int *positionP, int depth, int alpha, int beta, bool maximize,
                      vector<int *> freeSquares);

    int checkPoints(int position[], vector<int *> freeSquares);

    vector<int *> possibleMoves(int *position, vector<int *> board);
};


#endif //UNTITLED_AI_H
