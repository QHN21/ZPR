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
  void deleteGame(int gameID);
  const char* move(int gameID, int position);
  const char* gameState(int gameID);
};

#endif
