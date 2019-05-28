//
// Created by Krzysztof Bednarski on 28.03.2019.
//



#include "Player.h"

/**
 * Metoda pozwala na wykonanie ruchu gracza lub przeciwnika
 * @param x - wiersz na ktory ma byc wykonany ruch
 * @param y - kolumna na ktora ma byc wykonany ruch
 * @return - zwraca bool czy wykonanie ruchu sie powiodlo
 */
bool Player::move(int x, int y) {
    vector<int *> moves;
    //Sprawdza czy kafelek jest wolny czy nie
    if (checkMove(x, y)) {
        //Mozliwe do wykonania ruchy
        moves = possibleMoves();
        for (int i = 0; i < moves.size(); ++i) {
            //Sprawdza czy wspolrzedne na ktore ma byc wykonany ruch, sa mozliwe do wykonania
            if (moves[i][0] == x && moves[i][1] == y) {
                position[0] = x;
                position[1] = y;
                board->getSquares()[(x * 7) + y]->setFree(false);
                return true;
            }
        }
        return false;
    } else
        return false;
}

/**
 * Metoda pozwala na usuniecie, wybranego kafelka z planszy
 * @param x - wiersz usuwanego kafelka
 * @param y - kolumna usuwanego kafelka
 * @return - zwraca bool czy usuwanie sie powiodlo
 */
bool Player::hideSquare(int x, int y) {
    //Sprawdza czy kafelek jest jeszcze wolny
    if (checkMove(x, y)) {
        board->getSquares()[(x * 7) + y]->setFree(false);
        return true;
    } else
        return false;
}

/**
 * Sprawdza czy kafelek o podanych wspolrzednych jest wolny
 * @param x - wiersz kafelka
 * @param y - kolumna kafelka
 * @return - zwraca bool czy wolny czy nie
 */
bool Player::checkMove(int x, int y) {
    return board->isLegal(x, y);
}

/**
 * @return - zwraca pozycje gracza lub przeciwnika
 */
int *Player::getPosition() {
    return position;
}

/**
 * @return - zwraca wszystkie mozliwe do wykonania ruchy dla gracza lub przeciwnika
 */
vector<int *> Player::possibleMoves() {
    vector<int *> moves;
    vector<int*> freeSquares = board->getFreeSquares();

    for(int i = 0; i < freeSquares.size(); i++) {

        //Sprawdzamy pola wewnatrz planszy, bez uwzglednienia torusa
        if (freeSquares[i][0] - position[0] >= -1 && freeSquares[i][0] - position[0] <= 1) {
            if (freeSquares[i][1] - position[1] >= -1 && freeSquares[i][1] - position[1] <= 1) {
                if (!(freeSquares[i][0] == position[0] && freeSquares[i][1] == position[1])) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
            }
        }

        if (position[0] == 0 && position[1] >= 1 && position[1] <= 5 && freeSquares[i][0] == 6) {
            if (freeSquares[i][1] == position[1] || freeSquares[i][1] == position[1] + 1 || freeSquares[i][1] == position[1] - 1) {
                moves.push_back(freeSquares[i]);
                continue;
            }
        }

        if (position[0] == 6 && position[1] >= 1 && position[1] <= 5 && freeSquares[i][0] == 0) {
            if (freeSquares[i][1] == position[1] || freeSquares[i][1] == position[1] + 1 || freeSquares[i][1] == position[1] - 1) {
                moves.push_back(freeSquares[i]);
                continue;
            }
        }

        if (position[1] == 0 && position[0] >= 1 && position[0] <= 5 && freeSquares[i][1] == 6) {
            if (freeSquares[i][0] == position[0] || freeSquares[i][0] == position[0] + 1 || freeSquares[i][0] == position[0] - 1) {
                moves.push_back(freeSquares[i]);
                continue;
            }
        }

        if (position[1] == 6 && position[0] >= 1 && position[0] <= 5 && freeSquares[i][1] == 0) {
            if (freeSquares[i][0] == position[0] || freeSquares[i][0] == position[0] + 1 || freeSquares[i][0] == position[0] - 1) {
                moves.push_back(freeSquares[i]);
                continue;
            }
        }

        if (position[0] == 0) {
            if (position[1] == 0) {
                if (freeSquares[i][0] == 6 && (freeSquares[i][1] == 0 || freeSquares[i][1] == 1 || freeSquares[i][1] == 6)) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
                if (freeSquares[i][1] == 6 && (freeSquares[i][0] == 0 || freeSquares[i][0] == 1)) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
            }
            if (position[1] == 6) {
                if (freeSquares[i][0] == 6 && (freeSquares[i][1] == 6 || freeSquares[i][1] == 5 || freeSquares[i][1] == 0)) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
                if (freeSquares[i][1] == 0 && (freeSquares[i][0] == 0 || freeSquares[i][0] == 1)) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
            }
        }
        if (position[0] == 6) {
            if (position[1] == 0) {
                if (freeSquares[i][0] == 0 && (freeSquares[i][1] == 0 || freeSquares[i][1] == 1 || freeSquares[i][1] == 6)) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
                if (freeSquares[i][1] == 6 && (freeSquares[i][0] == 5 || freeSquares[i][0] == 6)) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
            }
            if (position[1] == 6) {
                if (freeSquares[i][0] == 0 && (freeSquares[i][1] == 6 || freeSquares[i][1] == 5 || freeSquares[i][1] == 0)) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
                if (freeSquares[i][1] == 0 && (freeSquares[i][0] == 6 || freeSquares[i][0] == 5)) {
                    moves.push_back(freeSquares[i]);
                    continue;
                }
            }
        }
    }
    return moves;
}

/**
 * Resetuje pozycje gracza do pozycji podanej w parametrach
 * @param x - wiersz
 * @param y - kolumna
 */
void Player::reset(int x, int y) {
	position[0] = x;
	position[1] = y;
	board->getSquares()[((x) * 7) + y]->setFree(false);
}
