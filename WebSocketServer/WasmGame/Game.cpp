
#include "Game.h"


/**
 * @return - zwraca numer ID gry
 */
int Game::getID(){
  return gameID;
}

/**
 * Wykonuje ruch podany od gracza i w zaleznosci od kontekstu
 * albo przemieszcza pionek gracza, albo usuwa pole i wywołuje algorytm
 * sztucznej inteligencji
 * @param x - nr wiersza klikniętego kafelka planszy
 * @param y - nr kolumny klikniętego kafelka planszy
 * @return - wskazanie na tablice char, w której znajdują się dane w postaci JSONa
 */
const char* Game::move(int x, int y){
  switch(turn){
    case player1Moves:
      player1->move(x,y);
      turn = player1DeletesField;
    break;

    case player1DeletesField:
    player1->hideSquare(x,y);
    if((player2 -> possibleMoves()).size() > 0){
      int *positionO = ai->minmax(player2->getPosition(), player1->getPosition(), difficulty, -1000000, 1000000, board->getFreeSquares());
      player2->move(positionO[0], positionO[1]);
      player2->hideSquare(positionO[2], positionO[3]);
      turn = player1Moves;
      if((player1 -> possibleMoves()).size() == 0){
        winner = 2;
        turn = game_ended;
      }
    }else{
      winner = 1;
      turn = game_ended;
    }
    break;

  }
  return getGameState();
}

/**
 * Resetuje gre do stanu początkowego i ustawia poziom trudności podany w argumencie
 * @param difficulty - poziom trudności podawany jako liczba całkowita (jest to głebokość drzewa poszukiwań)
 * @return - wskazanie na tablice char, w której znajdują się dane w postaci JSONa
 */
const char* Game::resetGame(int difficulty){
  this -> difficulty = difficulty;
  this -> winner = 0;
  this -> turn = player1Moves;
  this -> board -> reset();
  this -> player1 -> reset(3,6);
  this -> player2 -> reset(3,0);
  return getGameState();
}


/**
 * Uaktualnia tablicę gameStateJSON tworząc w niej JSONa przechowującego aktualny stan gry/
 * Znajdują się tam takie informacje jak pozycje graczy, wolne kafelki, możliwe ruchy, czy zwycięzca.
 * @return - wskazanie na tablice char, w której znajdują się dane w postaci JSONa
 */
const char* Game::getGameState(){
  vector<int *> freeSquares;
  vector<int *> possibleMoves;

  int gameboard[49] = {};
  int moves[49] = {};
  freeSquares  = board -> getFreeSquares();

  for(int i = 0; i< freeSquares.size(); i++){
    gameboard[freeSquares[i][0]+freeSquares[i][1]*7] = 1;
  }

  if(this->turn == player1Moves){
    possibleMoves = player1 -> possibleMoves();
    for(int i = 0; i< possibleMoves.size(); i++){
      moves[possibleMoves[i][0]+possibleMoves[i][1]*7] = 1;
    }
  }
  sprintf(gameStateJSON, "{\"player1\": %d,",(player1 ->getPosition())[0]+ (player1 ->getPosition())[1]*7 );
  sprintf(gameStateJSON, "%s\"player2\": %d,",gameStateJSON,(player2 ->getPosition())[0]+ (player2 ->getPosition())[1]*7 );


  sprintf(gameStateJSON, "%s\"gameboard\": [",gameStateJSON );
  for(int i = 0; i< 49; i++){
    sprintf(gameStateJSON, (i != 48) ? "%s%d," : "%s%d],",gameStateJSON,gameboard[i]);
  }
  sprintf(gameStateJSON, "%s\"possible_moves\": [",gameStateJSON );
  for(int i = 0; i< 49; i++){
    sprintf(gameStateJSON, (i != 48) ? "%s%d," : "%s%d],",gameStateJSON,(turn == player1DeletesField ) ?  gameboard[i] : moves[i]);
  }

  sprintf(gameStateJSON, "%s\"winner\": %d}",gameStateJSON, this->winner );
  return gameStateJSON;
}
