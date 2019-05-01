
//Global variables
const cells = document.querySelectorAll('.cell');
var player1 = {actCell: 0, playerCir:document.querySelector("#Pl1")};
var player2 = {actCell: 0, playerCir:document.querySelector("#Pl2")};
var possible_moves =[];

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
  player1.actCell = gameState.player1;
  player2.actCell = gameState.player2;
  possible_moves = gameState.possible_moves;
  drawGame();
};


//Game Drawing
function drawGame(){
  document.querySelector(".endgame").style.display = "none";
  moveTurn = 1;
  for(var i = 0; i <cells.length; i++){
    if(possible_moves[i] == 0){
      cells[i].style.backgroundColor = "white";
      cells[i].addEventListener('click',turnClick,false);
    }else{
      cells[i].style.backgroundColor = "black";
    }
  }
  player1.playerCir.style.backgroundColor = "red";
  move(cells[player1.actCell],player1);

  player2.playerCir.style.backgroundColor = "green";
  move(cells[player2.actCell],player2);
}

function reset(){
  var obj = {position: -1}
  ws.send(JSON.stringify(obj));
}

function turnClick(square){
  var position = parseInt(square.target.id);
  if(possible_moves[position] == 0){
    var obj = {position: parseInt(square.target.id)}
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
