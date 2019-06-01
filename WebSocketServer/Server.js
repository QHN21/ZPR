
const GameCreator = require('./Modules/GameCreator.js');

const gameCreator = new GameCreator();

//Server
const Client = require('./Modules/Client.js')
var WebSocketServer = require("ws").Server;
var wss = new WebSocketServer({ port: 3000});


console.log("Server Running");

wss.on('connection', function(ws) {
    ws.send(gameCreator.addGame(ws));

    ws.on('message', function(message){
      console.log("message " + gameCreator.findClientIndex(ws));
      var obj = JSON.parse(message);
      ws.send(gameCreator.updateGame(ws,obj));
    });

    ws.on('close', function(client){
      gameCreator.deleteGame(ws);
    });

    ws.on('error', function(client){
      gameCreator.deleteGame(ws);
    });
});
