#ifndef __GAME_H
#define __GAME_H


#include <vector>
#include <string>
#include "Board.h"
#include "Player.h"
#include "AI.h"

class Game{
private:
  enum game_state{
    game_ended = 0,
    player_1_moves = 1,
    player_1_deletes_field = 2,
  };

  int game_ID;
  int turn;
  int difficulty;
  int winner;

  std::shared_ptr<Board> board;
  Player* player_1;
  Player* player_2;
  AI* ai;

public:
  Game(int game_ID,int difficulty){
    this -> game_ID = game_ID;
    this -> difficulty = difficulty;
    this -> turn = player_1_moves;
    this -> winner = 0;
    board = std::make_shared<Board>();
    player_1 = new Player(board, 3, 6);
    player_2 = new Player(board, 3, 0);
    ai = new AI(board);
  }

  ~Game(){
      delete this -> player_1;
      delete this -> player_2;
      delete this -> ai;
      std::cout<<"Game Destroyed"<<std::endl;
  }

  int getID();


  const char* move(int x, int y);

  const char* reset_game(int difficulty);

  const char* getGameState();



};

#endif
