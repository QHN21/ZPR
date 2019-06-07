
#include "AI.h"

/**
 * Metoda implmentuje algorytm min-max z odcinaniem alpha-beta.
 * @param positionO - poczatkowa pozycja przeciwnika
 * @param positionP - poczatkowa pozycja gracza
 * @param depth - glebokosc przeszukiwania drzewa stanow
 * @param alpha - poczatkowa wartosc wspolczynnika alpha
 * @param beta - poczatkowa wartosc wspolczynnika beta
 * @param freeSquares - aktualnie wolne kafelki na planszy
 * @return - zwraca tablice 4 wartosci integer. 2 pierwsze to najlepszy znaleziony ruch gracza, a 2 kolejne to kafelek wybrany do usunięcia
 */
int *AI::minmax(int *positionO, int *positionP, int depth, int alpha, int beta, vector<int *> freeSquares) {
    int *maxVal = new int[4];
    int tmp;

    vector<int *> moves;
    //Pobranie wszystkich mozliwych ruchow w danym momencie
    moves = possibleMoves(positionO, freeSquares);
    if (moves.size() == 0) {
        maxVal[0] = -1;
        maxVal[1] = -1;
        maxVal[2] = -1;
        maxVal[3] = -1;
        return maxVal;
    }

    /*Dwie petle.Pierwsza iteruje po wszystkich mozliwych ruchach, a druga w kazdym obiegu petli usuwa inny
     * kafelek planszy, po to aby rozwazyc wszystkie mozliwosci(ruch + usuniety kafelek)
     * */
    for (int i = 0; i < moves.size(); i++) {
        for (int j = 0; j < freeSquares.size() - 1; j++) {
            vector<int *> freeCopy;
            freeCopy = freeSquares;
            //Jesli kafelek do usuniecia jest taki sam jak rozwazany ruch, to pomin ta iteracje
            if (moves[i][0] == *(freeCopy.begin() + j)[0] && moves[i][1] == *(freeCopy.begin() + j)[1])
                continue;
            //Usuwanie innego kafelka z planszy
            freeCopy.erase(freeCopy.begin() + j);

            //Uruchomienie algorytmu min-max dla wszystkich mozliwych kombinacji(ruch + usuniety kafelek)
            tmp = minmax_leaves(moves[i], positionP, depth - 1, alpha, beta, false, freeCopy);
            //Jesli wartosc zwrocona wieksza od aplha, to znaczy ze znaleziono lepsza kombinacje ruchu dla przeciwnika
            if (alpha < tmp) {
                alpha = tmp;
                maxVal[0] = moves[i][0];
                maxVal[1] = moves[i][1];
                maxVal[2] = freeSquares[j][0];
                maxVal[3] = freeSquares[j][1];
            }
        }
    }
    return maxVal;
}

/**
 * Metoda implmentuje algorytm min-max z odcinaniem alpha-beta.
 * @param positionO - poczatkowa pozycja przeciwnika
 * @param positionP - poczatkowa pozycja gracza
 * @param depth - glebokosc przeszukiwania drzewa stanow
 * @param alpha - poczatkowa wartosc wspolczynnika alpha
 * @param beta - poczatkowa wartosc wspolczynnika beta
 * @param maximize - jesli wartosc true to w danym wezle maksymalizujemy wartosc(ruch przeciwnika), jesli false to minimalizujemy(ruch gracza)
 * @param freeSquares - aktualnie rozważane ułożenie wolnych kafelkow na planszy
 * @return - zwraca wartość heurystki
 */
int AI::minmax_leaves(int *positionO, int *positionP, int depth, int alpha, int beta, bool maximize,
                      vector<int *> freeSquares) {
    int tmp;

    vector<int *> moves;
    //Pobranie wszystkich mozliwych ruchow w danym momencie. Jesli maximize==true, to pobieramy ruchy dla przeciwnika
    if (maximize)
        moves = possibleMoves(positionO, freeSquares);
    else
        moves = possibleMoves(positionP, freeSquares);

    //Jesli glebokosc depth == 0 lub brak mozliwosci ruchow, zwroc wartosc heurystyki, dla danego wezla
    if (depth == 0 || moves.size() == 0) {
        return checkPoints(positionO, freeSquares) - checkPoints(positionP, freeSquares);
    }

    /*Dwie petle.Pierwsza iteruje po wszystkich mozliwych ruchach, a druga w kazdym obiegu petli usuwa inny
     * kafelek planszy, po to aby rozwazyc wszystkie mozliwosci(ruch + usuniety kafelek)
     * */
    for (int i = 0; i < moves.size(); i++) {
        for (int j = 0; j < freeSquares.size() - 1; j++) {
            if (maximize) {
                vector<int *> freeCopy;
                freeCopy = freeSquares;
                //Jesli kafelek do usuniecia jest taki sam jak rozwazany ruch, to pomin ta iteracje
                if (moves[i][0] == *(freeCopy.begin() + j)[0] && moves[i][1] == *(freeCopy.begin() + j)[1])
                    continue;
                //Usuwanie innego kafelka z planszy
                freeCopy.erase(freeCopy.begin() + j);
                //Uruchomienie algorytmu min-max dla wszystkich mozliwych kombinacji(ruch + usuniety kafelek)
                tmp = minmax_leaves(moves[i], positionP, depth - 1, alpha, beta, false, freeCopy);
                //Jesli wartosc zwrocona wieksza od aplha, to znaczy ze znaleziono lepsza kombinacje ruchu dla przeciwnika
                if (alpha < tmp) {
                    alpha = tmp;
                }
                //Gdy alpha jest wieksze rowne beta, to odetnij reszte wezlow
                if (alpha >= beta)
                    break;
            } else {
                vector<int *> freeCopy;
                freeCopy = freeSquares;
                if (moves[i][0] == *(freeCopy.begin() + j)[0] && moves[i][1] == *(freeCopy.begin() + j)[1])
                    continue;
                freeCopy.erase(freeCopy.begin() + j);
                tmp = minmax_leaves(positionO, moves[i], depth - 1, alpha, beta, true, freeCopy);
                //Jesli wartosc zwrocona mniejsza od beta, to znaczy ze znaleziono lepsza dla gracza kombinacje ruchu
                if (beta > tmp) {
                    beta = tmp;
                }
                if (alpha >= beta)
                    break;
            }
        }
        //Gdy alpha jest wieksze rowne beta, to odetnij reszte wezlow
        if (alpha >= beta)
            break;
    }
    //Jesli w danym wezle rozwazany ruch maksymalizujacy to zwroca alpha, a jesli minimalizujacy to beta
    if (maximize) {
        return alpha;
    } else {
        return beta;
    }
}

/**
 * Oblicza punkty dla aktualnie rozwazanej pozycji. Sprawdzane jest ile mozliwych ruchow mozna wykonac w danym ustawieniu.
 * Kazdy mozliwy ruch zwieksza punktacje.
 * @param position - aktualnie rozwazana pozycja przeciwnika/gracza
 * @param freeSquares - aktualne ułożenie wolnych kafelków na planszy
 * @return - zwraca wartosc punktacji przeciwnika
 */
int AI::checkPoints(int *position, vector<int *> freeSquares) {
    return possibleMoves(position, freeSquares).size();
}

/**
 * Dla podanej pozycji gracza/przeciwnika i aktualnie wolnych kafelkow na planszy zwraca mozliwe ruchy z danej pozycji.
 * @param position - aktualna pozycja gracza/przeciwnika
 * @param board - aktualnie wolne kafelki na planszy
 * @return - zwraca wszystkie mozliwe ruchy
 */
vector<int *> AI::possibleMoves(int *position, vector<int *> board) {
    vector<int *> moves;
    for (int i = 0; i < board.size(); i++) {
        if (board[i][0] - position[0] >= -1 && board[i][0] - position[0] <= 1) {
            if (board[i][1] - position[1] >= -1 && board[i][1] - position[1] <= 1) {
                if (!(board[i][0] == position[0] && board[i][1] == position[1])) {
                    moves.push_back(board[i]);
                    continue;
                }
            }
        }

        if (position[0] == 0 && position[1] >= 1 && position[1] <= 5 && board[i][0] == 6) {
            if (board[i][1] == position[1] || board[i][1] == position[1] + 1 || board[i][1] == position[1] - 1) {
                moves.push_back(board[i]);
                continue;
            }
        }

        if (position[0] == 6 && position[1] >= 1 && position[1] <= 5 && board[i][0] == 0) {
            if (board[i][1] == position[1] || board[i][1] == position[1] + 1 || board[i][1] == position[1] - 1) {
                moves.push_back(board[i]);
                continue;
            }
        }

        if (position[1] == 0 && position[0] >= 1 && position[0] <= 5 && board[i][1] == 6) {
            if (board[i][0] == position[0] || board[i][0] == position[0] + 1 || board[i][0] == position[0] - 1) {
                moves.push_back(board[i]);
                continue;
            }
        }

        if (position[1] == 6 && position[0] >= 1 && position[0] <= 5 && board[i][1] == 0) {
            if (board[i][0] == position[0] || board[i][0] == position[0] + 1 || board[i][0] == position[0] - 1) {
                moves.push_back(board[i]);
                continue;
            }
        }

        if (position[0] == 0) {
            if (position[1] == 0) {
                if (board[i][0] == 6 && (board[i][1] == 0 || board[i][1] == 1 || board[i][1] == 6)) {
                    moves.push_back(board[i]);
                    continue;
                }
                if (board[i][1] == 6 && (board[i][0] == 0 || board[i][0] == 1)) {
                    moves.push_back(board[i]);
                    continue;
                }
            }
            if (position[1] == 6) {
                if (board[i][0] == 6 && (board[i][1] == 6 || board[i][1] == 5 || board[i][1] == 0)) {
                    moves.push_back(board[i]);
                    continue;
                }
                if (board[i][1] == 0 && (board[i][0] == 0 || board[i][0] == 1)) {
                    moves.push_back(board[i]);
                    continue;
                }
            }
        }
        if (position[0] == 6) {
            if (position[1] == 0) {
                if (board[i][0] == 0 && (board[i][1] == 0 || board[i][1] == 1 || board[i][1] == 6)) {
                    moves.push_back(board[i]);
                    continue;
                }
                if (board[i][1] == 6 && (board[i][0] == 5 || board[i][0] == 6)) {
                    moves.push_back(board[i]);
                    continue;
                }
            }
            if (position[1] == 6) {
                if (board[i][0] == 0 && (board[i][1] == 6 || board[i][1] == 5 || board[i][1] == 0)) {
                    moves.push_back(board[i]);
                    continue;
                }
                if (board[i][1] == 0 && (board[i][0] == 6 || board[i][0] == 5)) {
                    moves.push_back(board[i]);
                    continue;
                }
            }
        }
    }
    return moves;
}
