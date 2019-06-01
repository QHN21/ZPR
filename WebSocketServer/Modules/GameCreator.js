const Client = require('./Client.js')
const Mod = require('./WasmGame.js');
const WasmGame = Mod({wasmBinaryFile: 'WasmGame.wasm'});
WasmGame.onRuntimeInitialized = function() {
    console.log("Wasm Ready");
};

class GameCreator{
    constructor() {
      this.maxID = 0;
      this.clients = [];
    }

  addGame(ws){
    var difficulty = 2;
    var gameID = this.maxID++;
    this.clients.push(new Client(ws, gameID));
    console.log(`Number of connected clients: ${this.clients.length}`);
    WasmGame._new_game(gameID,difficulty);
    var ptr = WasmGame._gameState(gameID);
    var str = WasmGame.UTF8ToString(ptr,500);
    return str;
  }

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

  deleteGame(ws){
    var gameID = this.clients[this.findClientIndex(ws)].getGameID();
    WasmGame._deleteGame(gameID);
    this.clients.splice(this.findClientIndex(ws),1)
    console.log("DISCONNECTED");
    console.log(`Number of connected clients: ${this.clients.length}`);
  }


  getMaxID(){
    return this.maxID;
  }

  findClientIndex(ws){
    for(var i = 0; i < this.clients.length; i++){
      if(this.clients[i].getWebSocket() == ws){
        return i;
      }
    }
  }
}

module.exports = GameCreator;
