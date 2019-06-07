CALL emcc ./WebSocketServer/WasmGame/WasmAPI.cpp ./WebSocketServer/WasmGame/GamesHandler.cpp ./WebSocketServer/WasmGame/Game.cpp ./WebSocketServer/WasmGame/Board.cpp ./WebSocketServer/WasmGame/Square.cpp ./WebSocketServer/WasmGame/AI.cpp ./WebSocketServer/WasmGame/Player.cpp -O2 -s WASM=1 -Wall -s MODULARIZE=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=["UTF8ToString"] -o WasmGame.js
CALL move ./WasmGame.js ./WebSocketServer/Modules/WasmGame.js
CALL move ./WasmGame.wasm ./WebSocketServer/Modules/WasmGame.wasm
