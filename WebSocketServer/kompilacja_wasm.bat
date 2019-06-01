CALL emcc ./WasmGame/WasmAPI.cpp ./WasmGame/GamesHandler.cpp ./WasmGame/Game.cpp ./WasmGame/Board.cpp ./WasmGame/Square.cpp ./WasmGame/AI.cpp ./WasmGame/Player.cpp -O2 -s WASM=1 -Wall -s MODULARIZE=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=["UTF8ToString"] -o WasmGame.js
CALL move ./WasmGame.js ./Modules/WasmGame.js
CALL move ./WasmGame.wasm ./Modules/WasmGame.wasm
