const Client = require('./Client.js')
const Mod = require('./WasmGame.js');
const WasmGame = Mod({wasmBinaryFile: 'WasmGame.wasm'});
WasmGame.onRuntimeInitialized = function() {
    console.log("Wasm Ready");
};

class GameCreator{
    constructor() {
      this.maxID = 0;
      this.CLIENTS = [];
    }

  addGame(ws){
    var difficulty = 2;
    var gameID = this.maxID++;
    this.CLIENTS.push(new Client(ws, gameID));
    console.log(gameID);
    WasmGame._new_game(gameID,difficulty);
    var ptr = WasmGame._game_state(gameID);
    var str = WasmGame.UTF8ToString(ptr,500);
    return str;
  }

  updateGame(ws,obj){
    var gameID = this.CLIENTS[this.findClientIndex(ws)].getGameID();
    if(obj.reset == 0){
      //var game_info = GAMES[CLIENTS.indexOf(ws)].move(obj.position);
        var ptr = WasmGame._wasm_move(gameID,obj.position);
        var str = WasmGame.UTF8ToString(ptr,500);
        return str;
    }else {
      var ptr = WasmGame._reset_game(gameID,obj.difficulty);
      var str = WasmGame.UTF8ToString(ptr,500);
      return str;
    }
  }

  deleteGame(ws){
    var gameID = this.CLIENTS[this.findClientIndex(ws)].getGameID();
    WasmGame._delete_game(gameID);
    this.CLIENTS.splice(this.findClientIndex(ws),1)
    console.log("DISCONNECTED");
    console.log(`Number of connected clients: ${this.CLIENTS.length}`);
  }


  getMaxID(){
    return this.maxID;
  }

  findClientIndex(ws){
    for(var i = 0; i < this.CLIENTS.length; i++){
      if(this.CLIENTS[i].getWebSocket() == ws){
        return i;
      }
    }
  }
}

module.exports = GameCreator;
