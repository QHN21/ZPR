#ifndef __GAME_HANDLER_H
#define __GAME_HANDLER_H

#include <vector>
#include <string>
#include "Game.h"


class GamesHandler{
private:
  std::vector<Game*> games;
  GamesHandler(){};
public:
  static GamesHandler& getInstance();
  void addNewGame(int gameID, int difficulty);
  const char* resetGame(int gameId, int difficulty);
  void delete_game(int game_id);
  const char* move(int game_id, int position);
  const char* game_state(int game_id);
};

#endif
