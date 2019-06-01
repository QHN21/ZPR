
class Client{
    constructor(ws, gameID) {
      this.WebSocket = ws;
      this.gameID = gameID;
    }

  getWebSocket(){
    return this.WebSocket;
  }
  getGameID(){
    return this.gameID;
  }
}

module.exports = Client;
