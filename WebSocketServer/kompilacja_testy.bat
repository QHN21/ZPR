CD .\WasmGame\Tests
CALL g++ test.cpp ..\Square.cpp ..\Board.cpp ..\Player.cpp ..\Game.cpp ..\GamesHandler.cpp ..\AI.cpp -o test
CALL .\test
CD ..\..
