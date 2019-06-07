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

#include "GamesHandler.h"


/**
 * Funkcja odpowiedzialna za odebranie polecenia z JS o stworzenie nowej gry 
 * @param gameId - numer ID gry
 * @param difficulty - poziom trudnosci
 */
EM_PORT_API(void) new_game(int gameID, int difficulty) {
    GamesHandler::getInstance().addNewGame(gameID,difficulty);
    return;
}
/**
 * Funkcja odpowiedzialna za odebranie polecenia o resecie podanej gry z JS
 * @param gameId - numer ID gry
 * @param difficulty - poziom trudnosci
 * @retrun - zwraca aktualny stan gry
 */
EM_PORT_API(const char*) resetGame(int gameID, int difficulty) {
    return GamesHandler::getInstance().resetGame(gameID,difficulty);
}

/**
 * Funkcja odpowiedzialna za odebranie polecenia o usuniecie podanej gry z JS
 * @param gameId - numer ID gry
 * @retrun - zwraca aktualny stan gry
 */
EM_PORT_API(void) deleteGame(int gameID) {
    return GamesHandler::getInstance().deleteGame(gameID);
}

/**
 * Funkcja odpowiedzialna za odebranie polecenia o wykonaniu ruchu z JS
 * @param gameId - numer ID gry
 * @param position - pozycja podawana jako index kafelka
 * @retrun - zwraca aktualny stan gry
 */
EM_PORT_API(const char*) move(int gameID, int position) {
    return GamesHandler::getInstance().move(gameID,position);
}

/**
 * Funkcja odpowiedzialna za przekazanie stanu gry z WASM do JS
 * @param gameId - numer ID gry
 * @retrun - zwraca aktualny stan gry
 */
EM_PORT_API(const char*) gameState(int gameID) {
    return GamesHandler::getInstance().gameState(gameID);
}
