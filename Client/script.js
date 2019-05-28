
//Global variables
const cells = document.querySelectorAll('.cell');
var player1 = {actCell: 0, playerCir:document.querySelector("#Pl1")};
var player2 = {actCell: 0, playerCir:document.querySelector("#Pl2")};
var possible_moves =[];
var gameboard = [];
var difficulty = 2;
//Server connection

var ws = new WebSocket('ws://localhost:3000');

ws.onopen = function() {
    console.log("Connected to Isola");
};

ws.onclose = function() {
  console.log("DISCONNECTED");
};

ws.onmessage = function(message){
  console.log(message.data);
  var gameState = JSON.parse(message.data);
  console.log(gameState);
  player1.actCell = gameState.player_1;
  player2.actCell = gameState.player_2;
  gameboard = gameState.gameboard;
  possible_moves = gameState.possible_moves;

  drawGame();
};


//Game Drawing
function drawGame(){
  document.querySelector(".endgame").style.display = "none";
  moveTurn = 1;
  for(var i = 0; i <cells.length; i++){
    if(gameboard[i] == 1){
      cells[i].style.backgroundColor = "white";
    }else{
      cells[i].style.backgroundColor = "black";
    }
    if(possible_moves[i] == 1){

        cells[i].style.backgroundColor = "yellow";
        cells[i].addEventListener('click',turnClick,false);
    }
  }



  player1.playerCir.style.backgroundColor = "green";
  move(cells[player1.actCell],player1);

  player2.playerCir.style.backgroundColor = "red";
  move(cells[player2.actCell],player2);

  test();
}

function reset(){
  var obj = {position: 0, difficulty: difficulty, reset: 1};
  ws.send(JSON.stringify(obj));
}

function turnClick(square){
  var position = parseInt(square.target.id);
  if(possible_moves[position] == 1){
    var obj = {position: parseInt(square.target.id) , difficulty: difficulty,reset: 0}
    console.log(obj);
    ws.send(JSON.stringify(obj));
  }
}

function move(cell,player){
  var rect = cell.getBoundingClientRect();
  player.playerCir.style.top = rect.top + 2 + "px";
  player.playerCir.style.left = rect.left + 2 + "px";
  player.actCell = cell.id;
}

window.onresize = function(event) {
      move(cells[player1.actCell],player1);
      move(cells[player2.actCell],player2);
};


function test(){
  var r = 0;
  var p = 0;
  for(var i = 0 ; i < 49 ; i++)
    {
      if(possible_moves[i] == 1){
        p = i;
        break;
      }

          if(i == 48){
              r = 1;
          }
    }


    var obj = {position: p , difficulty: difficulty,reset: r}
    console.log(obj);
    setTimeout(function(){
          ws.send(JSON.stringify(obj));
        }, 500);
}
