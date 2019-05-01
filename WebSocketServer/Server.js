//Wasm test

console.log("Server Running");

console.log("WASM test:");


const fs = require('fs');
const buf = fs.readFileSync('./test.wasm');
var typedArray = new Uint8Array(buf);
var myfoo;
const env = {
    memoryBase: 0,
    tableBase: 0,
    memory: new WebAssembly.Memory({
      initial: 256
    }),
    table: new WebAssembly.Table({
      initial: 0,
      element: 'anyfunc'
    })
  }

WebAssembly.instantiate(typedArray, {
  env: env
}).then(result => {
  //console.log(util.inspect(result, true, 0));
  console.log(result.instance.exports.foo(9));
  myfoo = result.instance.exports.foo;

  console.log(myfoo(12));
}).catch(e => {
  // error caught
  console.log(e);
});

//Server

var WebSocketServer = require("ws").Server;
const Game = require("./Game/Game.js")
var wss = new WebSocketServer({ port: 3000});
var CLIENTS = [];
var GAMES = [];
var iterator = 0;




wss.on('connection', function(ws) {
    CLIENTS.push(ws);
    GAMES.push(new Game())
    console.log("CONNECTED");
    console.log(`Number of connected clients: ${CLIENTS.length}`);
    ws.send(JSON.stringify(GAMES[CLIENTS.indexOf(ws)].gameState()));

    ws.on('message', function(message){
      var obj = JSON.parse(message);
      if(obj.position != -1){
        GAMES[CLIENTS.indexOf(ws)].move(obj.position);
      }else {
        GAMES[CLIENTS.indexOf(ws)].reset();
      }
      ws.send(JSON.stringify(GAMES[CLIENTS.indexOf(ws)].gameState()));
    });

    ws.on('close', function(client){
      GAMES.splice(CLIENTS.indexOf(client),1)
      CLIENTS.splice(CLIENTS.indexOf(client),1)
      console.log("DISCONNECTED");
      console.log(`Number of connected clients: ${CLIENTS.length}`);
    });

    ws.on('error', function(client){
      GAMES.splice(CLIENTS.indexOf(client),1)
      CLIENTS.splice(CLIENTS.indexOf(client),1)
      console.log("DISCONNECTED");
      console.log(`Number of connected clients: ${CLIENTS.length}`);
    });
});
