CD .\Tests
CALL g++ test.cpp ..\WebSocketServer\WasmGame\Square.cpp ..\WebSocketServer\WasmGame\Board.cpp ..\WebSocketServer\WasmGame\Player.cpp ..\WebSocketServer\WasmGame\Game.cpp ..\WebSocketServer\WasmGame\GamesHandler.cpp ..\WebSocketServer\WasmGame\AI.cpp -o test
CALL .\test
CD ..
