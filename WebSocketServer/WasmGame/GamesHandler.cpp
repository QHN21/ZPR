#include "GamesHandler.h"

GamesHandler& GamesHandler::getInstance() {
  static GamesHandler instance;
  return instance;
}

void GamesHandler::addNewGame(int gameID, int difficulty){
      games.push_back(new Game(gameID,difficulty));
}

const char* GamesHandler::resetGame(int gameId, int difficulty) {
    int gameNumber =0 ;
    while(games[gameNumber]->getID() != gameId) gameNumber++;
    return games[gameNumber] -> resetGame(difficulty);
}

void GamesHandler::deleteGame(int gameID) {
    int gameNumber =0;
    while(games[gameNumber]->getID() != gameID) gameNumber++;
    delete games[gameNumber];
    games.erase(games.begin() + gameNumber);
    return;
}

const char* GamesHandler::move(int gameID, int position) {
    int x = position%7;
    int y = position/7;

    int gameNumber =0 ;

    while(games[gameNumber]->getID() != gameID) gameNumber++;
    return games[gameNumber] -> move(x, y);
}



const char* GamesHandler::gameState(int gameID) {
    int gameNumber =0 ;
    while(games[gameNumber]->getID() != gameID) gameNumber++;
    return games[gameNumber] -> getGameState();
}
