#include "GamesHandler.h"


/**
 * Funkcja odpowiedzialna za dostęp do singletona
 * @return - zwraca instancję klasy
 */
GamesHandler& GamesHandler::getInstance() {
  static GamesHandler instance;
  return instance;
}


/**
 * Funkcja odpowiedzialna za tworzenie nowej gry o podanym id i poziomie trudnosci
 * @param gameId - numer ID gry
 * @param difficulty - poziom trudnośći
 */
void GamesHandler::addNewGame(int gameID, int difficulty){
      games.push_back(new Game(gameID,difficulty));
}


/**
 * Funkcja odpowiedzialna za resetowanej gry o podanym id i ustawienie jej podanego poziomu trudności
 * @param gameId - numer ID gry
 * @param difficulty - poziom trudnośći
 * @retrun - zwraca aktualny stan gry
 */
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


/**
 * Funkcja odpowiedzialna za wykonanie ruchu w grze o podanym id,
 * na podstawie pozycji kafelka planszy podanej w zmiennej position
 * @param gameId - numer ID gry
 * @param position - pozycja podawana jako index kafelka
 * @retrun - zwraca aktualny stan gry
 */
const char* GamesHandler::move(int gameID, int position) {
    int x = position%7;
    int y = position/7;

    int gameNumber =0 ;

    while(games[gameNumber]->getID() != gameID) gameNumber++;
    return games[gameNumber] -> move(x, y);
}


/**
 * Funkcja odpowiedzialna za zwrócnie aktualnego stanu gry o podanym id
 * @param gameId - numer ID gry
 * @retrun - zwraca aktualny stan gry
 */
const char* GamesHandler::gameState(int gameID) {
    int gameNumber =0 ;
    while(games[gameNumber]->getID() != gameID) gameNumber++;
    return games[gameNumber] -> getGameState();
}
