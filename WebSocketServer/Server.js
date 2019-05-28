//WASM
const Mod = require('./WasmGame.js');
const WasmGame = Mod({wasmBinaryFile: 'WasmGame.wasm'});
WasmGame.onRuntimeInitialized = function() {
    console.log("Wasm Ready");
};


//Server

var WebSocketServer = require("ws").Server;
var wss = new WebSocketServer({ port: 3000});
var CLIENTS = [];
var maxID = 0;


console.log("Server Running");


wss.on('connection', function(ws) {
    CLIENTS.push(ws);
    //GAMES.push(new Game(CLIENTS.indexOf(ws), WasmGame));
    WasmGame._new_game(CLIENTS.indexOf(ws),1);
    console.log("CONNECTED");
    console.log(`Number of connected clients: ${CLIENTS.length}`);

 var ptr = WasmGame._game_state(CLIENTS.indexOf(ws));

 var str = WasmGame.UTF8ToString(ptr,500);
    ws.send(str);

    ws.on('message', function(message){
      console.log("message");
      var obj = JSON.parse(message);

      if(obj.reset == 0){
        //var game_info = GAMES[CLIENTS.indexOf(ws)].move(obj.position);
          var ptr = WasmGame._wasm_move(CLIENTS.indexOf(ws),obj.position);
          var str = WasmGame.UTF8ToString(ptr,500);
          ws.send( str);

      }else {
        var ptr = WasmGame._reset_game(CLIENTS.indexOf(ws),obj.difficulty);
        var str = WasmGame.UTF8ToString(ptr,500);
        ws.send( str);
      }
      //ws.send(game_info);
    });

    ws.on('close', function(client){
      WasmGame._delete_game(CLIENTS.indexOf(ws));
      CLIENTS.splice(CLIENTS.indexOf(ws),1)
      console.log("DISCONNECTED");
      console.log(`Number of connected clients: ${CLIENTS.length}`);
    });

    ws.on('error', function(client){
      WasmGame._delete_game(CLIENTS.indexOf(ws));
      CLIENTS.splice(CLIENTS.indexOf(ws),1)
      console.log("DISCONNECTED");
      console.log(`Number of connected clients: ${CLIENTS.length}`);
    });
});
