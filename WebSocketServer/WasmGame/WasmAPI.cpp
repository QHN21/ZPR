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

EM_PORT_API(void) new_game(int game_id, int difficulty) {
    GamesHandler::getInstance().addNewGame(game_id,difficulty);
    return;
}

EM_PORT_API(const char*) reset_game(int game_id, int difficulty) {
    return GamesHandler::getInstance().resetGame(game_id,difficulty);
}

EM_PORT_API(void) delete_game(int game_id) {
    return GamesHandler::getInstance().delete_game(game_id);
}


EM_PORT_API(const char*) wasm_move(int game_id, int position) {
    return GamesHandler::getInstance().move(game_id,position);
}


EM_PORT_API(const char*) game_state(int game_id) {
    return GamesHandler::getInstance().game_state(game_id);
}
