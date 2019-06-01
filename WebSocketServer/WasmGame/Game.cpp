#ifndef EM_PORT_API
#    if defined(__EMSCRIPTEN__)
#        include <emscripten.h>
#        if defined(__cplusplus)
#            define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#        else
#            define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#        endif
#    else
#        if defined(__cplusplus)
#            define EM_PORT_API(rettype) extern "C" rettype
#        else
#            define EM_PORT_API(rettype) rettype
#        endif
#    endif
#endif

#include <vector>
#include <string>
#include "Board.h"
#include "Player.h"
#include "AI.h"

enum difficulty{
  easy = 1,
  medium = 2,
  hard = 3
};

enum game_state{
  game_ended = 0,
  player_1_moves = 1,
  player_1_deletes_field = 2,
};

class Game{
private:
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
      //delete this -> board;
      delete this -> player_1;
      delete this -> player_2;
      delete this -> ai;
      std::cout<<"Game Destroyed"<<std::endl;
  }

  int getID(){
    return game_ID;
  }


  const char* move(int x, int y){
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

  const char* reset_game(int difficulty){
    this -> difficulty = difficulty;
    this -> winner = 0;
    this -> turn = player_1_moves;
    this -> board -> reset();
    this -> player_1 -> reset(3,6);
    this -> player_2 -> reset(3,0);
    return getGameState();
  }

  const char* getGameState(){
    char str[500];
    vector<int *> freeSquares;
    vector<int *> possibleMoves;

    int gameboard[49] = {};
    int moves[49] = {};
    freeSquares  = board -> getFreeSquares();

    for(int i = 0; i< freeSquares.size(); i++){
      gameboard[freeSquares[i][0]+freeSquares[i][1]*7] = 1;
    }

    if(turn == player_1_moves){
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



};

std::vector<Game*> games;


EM_PORT_API(int) new_game(int game_id, int difficulty) {
    games.push_back(new Game(game_id,difficulty));
    std::cout<<"Game Created"<<std::endl;
    return games.size()-1;
}

EM_PORT_API(const char*) reset_game(int game_id, int difficulty) {
    int game_number =0 ;

    while(games[game_number]->getID() != game_id) game_number++;
    return games[game_number] -> reset_game(difficulty);
}

EM_PORT_API(int) delete_game(int game_id) {
    int game_number =0;
    while(games[game_number]->getID() != game_id) game_number++;
    delete games[game_number];
    games.erase(games.begin() + game_number);
    return 0;
}


EM_PORT_API(const char*) wasm_move(int game_id, int position) {
    int x = position%7;
    int y = position/7;

    int game_number =0 ;

    while(games[game_number]->getID() != game_id) game_number++;
    return games[game_number] -> move(x, y);
}


EM_PORT_API(const char*) game_state(int game_id) {
    int game_number =0 ;
    while(games[game_number]->getID() != game_id) game_number++;
    return games[game_number] -> getGameState();
}
