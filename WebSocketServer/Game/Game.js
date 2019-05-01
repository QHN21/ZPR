
const BOARDSIZE = 49;

class Game{
    constructor() {
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

  gameState(){
    var obj = {
      player1: this.player1,
      player2: this.player2,
      possible_moves: this.gameBoard
    };
    return obj;
  }

  move(position){
    switch (this.moveTurn) {
      case 1:
        this.player1 = position;
        this.gameBoard[position] = 1;
        this.moveTurn = 2;
        break;
      case 2:
        this.gameBoard[position] = 1;
        this.moveTurn = 3;
        break;
      case 3:
        this.player2 = position;
        this.gameBoard[position] = 1;
        this.moveTurn = 4;
        break;
      case 4:
        this.gameBoard[position] = 1;
        this.moveTurn = 1;
        break;
    }
  }
}

module.exports = Game;
