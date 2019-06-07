
const ClientCreator = require('./Modules/ClientCreator.js');

const clientCreator = new ClientCreator();

/**
 * Kod serwera.
 * Skrypt załącza potrzebne biblioteki, uruchamia serwer i oczekuje na połączenie od klienta.
 * Serwer odpowiedzialny jest za otrzymywanie połączeń i wiadomości od klientó i reagowanie na zgłoszone przez nich prośby.
 */
const Client = require('./Modules/Client.js')
var WebSocketServer = require("ws").Server;
var wss = new WebSocketServer({ port: 3000});


console.log("Server Running");

wss.on('connection', function(ws) {
    ws.send(clientCreator.addClient(ws));

    ws.on('message', function(message){
      console.log("message " + clientCreator.findClientIndex(ws));
      var obj = JSON.parse(message);
      ws.send(clientCreator.updateGame(ws,obj));
    });

    ws.on('close', function(client){
      console.log("CLIENT DISCONNECTED");
      console.log(`Number of connected clients: ${clientCreator.deleteGame(ws)}`);
    });

    ws.on('error', function(client){
        console.log("CLIENT DISCONNECTED, ERROR OCCURED");
        console.log(`Number of connected clients: ${clientCreator.deleteGame(ws)}`);
    });
});
