
#ifndef __BOARD_H
#define __BOARD_H

#include "Square.h"
#include <vector>

using namespace std;

/**
 * Klasa odpowidzialne za implementacje planszy
 */
class Board {
private:
    vector<Square *> squares;
public:
    //x - kol, y - wiersz
    Board() {
        for (int x = 0; x < 7; x++) {
            for (int y = 0; y < 7; y++) {
                Square *square = new Square(x, y);
                squares.push_back(square);
            }
        }
    }

    ~Board(){
      for (int i = 0; i < squares.size(); i++) {
          delete squares[i];
      }
    }

    vector<int *> getFreeSquares();

    bool isLegal(int x, int y);

    const vector<Square *> &getSquares();

	void reset();
};

#endif //UNTITLED_BOARD_H
