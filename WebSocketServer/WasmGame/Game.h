#ifndef __GAME_H
#define __GAME_H


#include <vector>
#include <string>
#include "Board.h"
#include "Player.h"
#include "AI.h"

class Game{
private:
  enum gameState{
    game_ended = 0,
    player1Moves = 1,
    player1DeletesField = 2,
  };

  int gameID;
  int turn;
  int difficulty;
  int winner;

  char gameStateJSON[500];

  std::shared_ptr<Board> board;
  Player* player1;
  Player* player2;
  AI* ai;

public:
  Game(int gameID,int difficulty){
    this -> gameID = gameID;
    this -> difficulty = difficulty;
    this -> turn = player1Moves;
    this -> winner = 0;
    board = std::make_shared<Board>();
    player1 = new Player(board, 3, 6);
    player2 = new Player(board, 3, 0);
    ai = new AI(board);
  }

  ~Game(){
      delete this -> player1;
      delete this -> player2;
      delete this -> ai;
  }

  int getID();


  const char* move(int x, int y);

  const char* resetGame(int difficulty);

  const char* getGameState();



};

#endif
