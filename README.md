# Przeglądarkowa gra w Izolację z wykorzystaniem WASM

Gra została stworzona jako zadanie projektowe z przedmiotu ZPR. Zasady gryw izolację można znaleźć na poniższej stronie: \
https://en.wikipedia.org/wiki/Isolation_(board_game) \
W naszej wersji plansza dodatkowo jest torusem (tzn. wychodząc za jedną strone planszy znajdujemy się po drugiej).
Gra odbywa się z algorytmem sztucznej inteligencji min-max z obcinaniem alfa-beta.

# Struktura projektu

Projekt składa się z dwóch części: 
1. **Aplikacji klienckiej**
2. **Serwera**

## Aplikacja kliencka

Tutaj zaimplementowane zostało GUI oraz łąćzność z serwerem, na którym znajduje się cała logika gry. 
Wykorzystanym językiem do utworzenia tej części był JavaScript.
Połączenie z serwerem odbywa się za pomocą WebSocket'ów

## Serwer

Serwer zajmuje się odbieraniem zapytań od klienta, regowanie, na nie oraz komunikację z modułem napisanym w WASM, 
Serwer został napisany w języku JavaScript i jest uruchamiany w środowisku node.js, natomiast moduł WASM, w którym znajduje się cała logika gry,
napisany jest w języku C++ i kompilowany do Web Assembly za pomocą kompilatora emscripten. Dwa języki komunikują się za pomocą 
specjalnego API, które udostępnia WASM.

# Instalacja Środowiska

Do uruchomienia aplikacji potrzebny jest jedynie node.js którego można pobrać ze strony: \
https://nodejs.org/en/  \
Do kompilacji kodu będzie potrzebny natomiast kompilator emscripten, którego instalation guide można znaleźć na stronie: \
https://3dgen.cn/cppwasm-book/en/ \
Dodatkowo zaleca się przeglądarki, które obsługują WebSocket takie jak Google Chrome czyMozilla Firefox

# Uruchomienie Aplikacji

Aby uruchomić aplikację należy pobrać omawiany i w wierszu polecenia przejść od folderu, w którym się znajduje.
Następnie przejść do folderu WebSocketServer i tam uruchomić serwer za pomocą komendy: \
*node Server.js* \
Kolejnym krokiem jest uruchomienie aplikacji klienckiej. Aby to zrobić należy przejść do folderu Client w projekcie 
i uruchomić plik *index.html*. Nastąpi wtedy połączenie z serwerem, co umożliwi rozegranie partii. \
Dodatkowo można w tym samym serwerze uruchomić *index_auto_player.html* który symuluje rozgrywkę innego klienta, 
co pozwala przetestować wydajność serwera w przypadku gdy zapytania wysyła więcej klientów.

# Kompilacja
Jedynymi modułami wymagającymi kompilacji jest moduł WASM, oraz moduł testowy.
## Kompilacja WASM
Aby skompilować moduł WASM należy wykonać kilka poniższe kroki:
1. Uruchom wiersz polecenia
2. Dołącz emscripten do zmiennych (proces ten jest omówiony w tutorialu udostępnionym w sekcji Instalacja)
3. Przejdź do folderu (ścieżka do folderu projektu)/WebSocketServer/WasmGame
4. Uruchom poniższe polecenie: \
*emcc ./WasmGame/WasmAPI.cpp ./WasmGame/GamesHandler.cpp ./WasmGame/Game.cpp ./WasmGame/Board.cpp ./WasmGame/Square.cpp ./WasmGame/AI.cpp ./WasmGame/Player.cpp -O2 -s WASM=1 -Wall -s MODULARIZE=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=["UTF8ToString"] -o WasmGame.js*
5. Wygenerowane pliki (WasmGame.js oraz WasmGame.wasm) przenieś do folderu (śzieżka do folderu projektu)/WebSocketServer/Modules
6. Gotowe!

Alternatywnie na systemie Windows 10:
1. Uruchom wiersz polecenia
2. Dołącz emscripten do zmiennych (proces ten jest omówiony w tutorialu udostępnionym w sekcji Instalacja)
3. Przejdź do folderu (ścieżka do folderu projektu)/WebSocketServer
4. Uruchom skrypt *kompilacja_wasm.bat*
## Kompilacja Testów
Aby skompilować i uruchomić testy należy posiadać dowolny kompilator C++. \
Aby tego dokonać:
1. Uruchom wiersz polecenia
2. Przejdź do folderu (ścieżka do folderu projektu)/WebSocketServer/WasmGame/Testy
3. Uruchom polecenie: \
*g++ test.cpp ..\Square.cpp ..\Board.cpp ..\Player.cpp ..\Game.cpp ..\GamesHandler.cpp ..\AI.cpp -o test*
4. Uruchom polecenie: \
*./test*

Alternatywnie na Windows 10:
1. Uruchom wiersz polecenia
2. Przejdź do folderu (ścieżka do folderu projektu)/WebSocketServer
3. Uruchom skrypt *kompilacja_testy.bat*

