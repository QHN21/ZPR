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

EM_PORT_API(void) new_game(int gameID, int difficulty) {
    GamesHandler::getInstance().addNewGame(gameID,difficulty);
    return;
}

EM_PORT_API(const char*) resetGame(int gameID, int difficulty) {
    return GamesHandler::getInstance().resetGame(gameID,difficulty);
}

EM_PORT_API(void) deleteGame(int gameID) {
    return GamesHandler::getInstance().deleteGame(gameID);
}


EM_PORT_API(const char*) move(int gameID, int position) {
    return GamesHandler::getInstance().move(gameID,position);
}


EM_PORT_API(const char*) gameState(int gameID) {
    return GamesHandler::getInstance().gameState(gameID);
}
