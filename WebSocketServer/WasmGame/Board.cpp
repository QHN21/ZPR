
#include "Board.h"

using namespace std;

/**
 * Sprawdza czy podany kafelek jest wolny czy nie.
 * @param x - nr wiersza sprawdzanego kafelka
 * @param y - nr kolumny sprawdzanego kafelka
 * @return - zwraca true jesli wolny lub false jesli nie
 */
bool Board::isLegal(int x, int y) {
    return squares[(x * 7) + y]->getFree();
}

/**
 * @return zwraca wszystkie kafelki
 */
const vector<Square *> &Board::getSquares() {
    return squares;
}

/**
 * @return - zwraca wszystkie wolne kafelki na planszy
 */
vector<int *> Board::getFreeSquares() {
    vector<int *> freeSquares;
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            if (isLegal(x, y))
                freeSquares.push_back(squares[x * 7 + y]->getPosition());
        }
    }
    return freeSquares;
}

/**
 * Resetuje plansze do warto�ci pocz�tkowej
 */
void Board::reset() {
	for (int i = 0; i < squares.size(); i++) {
		squares[i]->setFree(true);
	}
}
