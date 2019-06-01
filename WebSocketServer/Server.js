//WASM
/**
*/
const Mod = require('./WasmGame.js');
const WasmGame = Mod({wasmBinaryFile: 'WasmGame.wasm'});
WasmGame.onRuntimeInitialized = function() {
    console.log("Wasm Ready");
};


//Server
const Client = require('./Client/Client.js')
var WebSocketServer = require("ws").Server;
var wss = new WebSocketServer({ port: 3000});
var CLIENTS = [];
var maxID = 0;


console.log("Server Running");

function findClient(ws){
  for(var i = 0; i < CLIENTS.length; i++){
    if(CLIENTS[i].getWebSocket() == ws){
      return i;
    }
  }
}

wss.on('connection', function(ws) {
    CLIENTS.push(new Client(ws, maxID++));

    console.log(CLIENTS[findClient(ws)].getGameID());
    WasmGame._new_game(CLIENTS[findClient(ws)].getGameID(),1);
    console.log("CONNECTED");
    console.log(`Number of connected clients: ${CLIENTS.length}`);

 var ptr = WasmGame._game_state(CLIENTS[findClient(ws)].getGameID());

 var str = WasmGame.UTF8ToString(ptr,500);
    ws.send(str);

    ws.on('message', function(message){
      console.log("message " + findClient(ws) );
      var obj = JSON.parse(message);

      if(obj.reset == 0){
        //var game_info = GAMES[CLIENTS.indexOf(ws)].move(obj.position);
          var ptr = WasmGame._wasm_move(CLIENTS[findClient(ws)].getGameID(),obj.position);
          var str = WasmGame.UTF8ToString(ptr,500);
          ws.send( str);

      }else {
        var ptr = WasmGame._reset_game(CLIENTS[findClient(ws)].getGameID(),obj.difficulty);
        var str = WasmGame.UTF8ToString(ptr,500);
        ws.send( str);
      }
      //ws.send(game_info);
    });

    ws.on('close', function(client){
      WasmGame._delete_game(CLIENTS[findClient(ws)].getGameID());
      CLIENTS.splice(findClient(ws),1)
      console.log("DISCONNECTED");
      console.log(`Number of connected clients: ${CLIENTS.length}`);
    });

    ws.on('error', function(client){
      WasmGame._delete_game(CLIENTS[findClient(ws)].getGameID());
      CLIENTS.splice(findClient(ws),1)
      console.log("DISCONNECTED");
      console.log(`Number of connected clients: ${CLIENTS.length}`);
    });
});
