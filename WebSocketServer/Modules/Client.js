
/**
 * Klasa odpowiedzialna za przechowywanie informacji o kliencie
 */
class Client{
    constructor(ws, gameID) {
      this.WebSocket = ws;
      this.gameID = gameID;
    }
/**
 * @return - zwraca wartość WebSocket danego klienta
 */
  getWebSocket(){
    return this.WebSocket;
  }
/**
 * @return - zwraca wartość identyfikatora gry kliena
 */
  getGameID(){
    return this.gameID;
  }
}

module.exports = Client;
