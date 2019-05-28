
const BOARDSIZE = 49;

class Game{
    constructor(gameID, wasmGame) {
      this.gameID = gameID;
      this.wasmGame = wasmGame;
      this.gameBoard = [BOARDSIZE];
      for(var i = 0; i< BOARDSIZE; i++){
        if(i != 3 && i != 45)
          this.gameBoard[i] = 0;
        else {
          this.gameBoard[i] = 1
        }
      }
      this.player1 = 3;
      this.player2 = 45;
      this.moveTurn = 1;
    }

  reset(){
  }

  move(position){
    var ptr = this.wasmGame._wasm_move(this.gameID,position);
    var str = this.wasmGame.UTF8ToString(ptr,500);
    return str;
  }

  gameState(){
    var ptr = this.wasmGame._game_state(this.gameID);
    var str = this.wasmGame.UTF8ToString(ptr,500);
    return str;
  }
}

module.exports = Game;
