
#include "Game.h"



int Game::getID(){
  return game_ID;
}


const char* Game::move(int x, int y){
  switch(turn){
    case player_1_moves:
      player_1->move(x,y);
      turn = player_1_deletes_field;
    break;

    case player_1_deletes_field:
    player_1->hideSquare(x,y);
    if((player_2 -> possibleMoves()).size() > 0){
      int *positionO = ai->minmax(player_2->getPosition(), player_1->getPosition(), difficulty, -1000000, 1000000, board->getFreeSquares());
      player_2->move(positionO[0], positionO[1]);
      player_2->hideSquare(positionO[2], positionO[3]);
      turn = player_1_moves;
    }else{
      winner = 1;
      turn = game_ended;
    }
    if((player_1 -> possibleMoves()).size() == 0){
      winner = 2;
      turn = game_ended;
    }
    break;

  }
  return getGameState();
}

const char* Game::reset_game(int difficulty){
  this -> difficulty = difficulty;
  this -> winner = 0;
  this -> turn = player_1_moves;
  this -> board -> reset();
  this -> player_1 -> reset(3,6);
  this -> player_2 -> reset(3,0);
  return getGameState();
}

const char* Game::getGameState(){
  char str[500];
  vector<int *> freeSquares;
  vector<int *> possibleMoves;

  int gameboard[49] = {};
  int moves[49] = {};
  freeSquares  = board -> getFreeSquares();

  for(int i = 0; i< freeSquares.size(); i++){
    gameboard[freeSquares[i][0]+freeSquares[i][1]*7] = 1;
  }

  if(this->turn == player_1_moves){
    possibleMoves = player_1 -> possibleMoves();
    for(int i = 0; i< possibleMoves.size(); i++){
      moves[possibleMoves[i][0]+possibleMoves[i][1]*7] = 1;
    }
  }
  sprintf(str, "{\"player_1\": %d,",(player_1 ->getPosition())[0]+ (player_1 ->getPosition())[1]*7 );
  sprintf(str, "%s\"player_2\": %d,",str,(player_2 ->getPosition())[0]+ (player_2 ->getPosition())[1]*7 );


  sprintf(str, "%s\"gameboard\": [",str );
  for(int i = 0; i< 49; i++){
    sprintf(str, (i != 48) ? "%s%d," : "%s%d],",str,gameboard[i]);
  }
  sprintf(str, "%s\"possible_moves\": [",str );
  for(int i = 0; i< 49; i++){
    sprintf(str, (i != 48) ? "%s%d," : "%s%d],",str,(turn == player_1_deletes_field ) ?  gameboard[i] : moves[i]);
  }

  sprintf(str, "%s\"winner\": %d}",str, this->winner );
  return str;
}
