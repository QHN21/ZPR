const Client = require('./Client.js')
const Mod = require('./WasmGame.js');
const WasmGame = Mod({wasmBinaryFile: 'WasmGame.wasm'});
WasmGame.onRuntimeInitialized = function() {
    console.log("Wasm Ready");
};

/**
 * Klasa odpowiedzialna za Tworzenie i przechowywanie klientów, komunikacje z modułem WASM oraz łączeniem graczy z ich grami
 */
class ClientCreator{
    constructor() {
      this.maxID = 0;
      this.clients = [];
    }
/**
 * Metoda odpowiedzialna za dodawanie klientów, tworzenie ich geier oraz łączenie ich z grami.
 * @param ws - wartośc WebSocket połączenia z klientem
 * @return - zwraca stan gry gracza w postaći stringa przechowującego obiekt JSON
 */
  addClient(ws){
    var difficulty = 2;
    var gameID = this.maxID++;
    this.clients.push(new Client(ws, gameID));
    console.log(`Number of connected clients: ${this.clients.length}`);
    WasmGame._new_game(gameID,difficulty);
    var ptr = WasmGame._gameState(gameID);
    var str = WasmGame.UTF8ToString(ptr,500);
    return str;
  }
  /**
   * Metoda odpowiedzialna za aktualizowanie gry klienta, na podstawie wyslanej wiadomości
   * @param ws - wartośc WebSocket połączenia z klientem
   * @param obj - obiekt JSON otrzymany w wiadomości od klienta, przechowuje dane o wykonanym ruchu
   * @return - zwraca stan gry gracza w postaći stringa przechowującego obiekt JSON
   */
  updateGame(ws,obj){
    var gameID = this.clients[this.findClientIndex(ws)].getGameID();
    if(obj.reset == 0){
        var ptr = WasmGame._move(gameID,obj.position);
        var str = WasmGame.UTF8ToString(ptr,500);
        return str;
    }else {
      var ptr = WasmGame._resetGame(gameID,obj.difficulty);
      var str = WasmGame.UTF8ToString(ptr,500);
      return str;
    }
  }

/**
 * Metoda odpowiedzialna za usunięcie gracza i skojarzonej z nim gry
 * @param ws - wartośc WebSocket połączenia z klientem
 * @param obj - obiekt JSON otrzymany w wiadomości od klienta, przechowuje dane o wykonanym ruchu
 * @return - zwraca aktualną ilość klientów
 */
  deleteGame(ws){
    var gameID = this.clients[this.findClientIndex(ws)].getGameID();
    WasmGame._deleteGame(gameID);
    this.clients.splice(this.findClientIndex(ws),1)
    return this.clients.length;
  }

/**
 * @return - zwraca wartość maksymalnego identyfikatora
 */
  getMaxID(){
    return this.maxID;
  }
/**
 * Metoda odpowiedzialna za znalezienie indeksu klienta
 * @param ws - wartośc WebSocket połączenia z klientem
 * @return - zwraca indeks klienta
 */
  findClientIndex(ws){
    for(var i = 0; i < this.clients.length; i++){
      if(this.clients[i].getWebSocket() == ws){
        return i;
      }
    }
  }
}

module.exports = ClientCreator;
