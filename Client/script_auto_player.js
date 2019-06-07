/**
 * Inicjalizacja zmiennych gry takich jak:
 * - komórki na planszy
 * - gracze
 * - zmienne przetrzymujące: możliwe ruchy, plansze gry, poziom trudności oraz informację o tym kto wygrał
 * @type {NodeListOf<cells,player1,player2,possible_moves,gameboard,difficulty,winner>}
 */
const cells = document.querySelectorAll('.cell');
var player1 = {actCell: 0, playerCir: document.querySelector("#Pl1")};
var player2 = {actCell: 0, playerCir: document.querySelector("#Pl2")};
var possible_moves = [];
var gameboard = [];
var difficulty = 2;
var winner = 0;

//Dodaje listenera, który nasłuchuje kliknięć myszą.
document.querySelector('.close').addEventListener('click', function () {
    drawGame();
});


/**
 * Obiekt odpowiedzialny za dostarczenie API do połączenia typu WebSocket pomiędzy klientem a serwerem.
 * @type {WebSocket}
 */
var ws = new WebSocket('ws://localhost:3000');

ws.onopen = function () {
    console.log("Connected to Isola");
};

/**
 * Funkcja uruchamiana przy zamykaniu połączenia z serwerem. Wyświetla okno informujące o braku łączności.
 */
ws.onclose = function () {
    console.log("DISCONNECTED");
    document.querySelector(".endgame").style.display = "none";
    document.querySelector(".wongame").style.display = "none";
    document.querySelector(".lostgame").style.display = "none";
    document.querySelector(".noconnection").style.display = "initial";
};


/**
 * Funkcja odpowiedzialna za przetwarzanie wiadomości otrzymanych od serwera.
 * @param message - wiadomość otrzymana od serwera
 */
ws.onmessage = function (message) {
    console.log(message.data);
    var gameState = JSON.parse(message.data);
    console.log(gameState);
    player1.actCell = gameState.player1;
    player2.actCell = gameState.player2;
    gameboard = gameState.gameboard;
    possible_moves = gameState.possible_moves;
    winner = gameState.winner;
    drawGame();
};


/**
 * Funkcja wykouje następujące działania:
 * - rysuje aktualną planszę gry
 * - rysuje graczy
 * - wyświetla okna z informacją, kto wygrał
 */
function drawGame() {
    document.querySelector(".endgame").style.display = "none";
    document.querySelector(".wongame").style.display = "none";
    document.querySelector(".lostgame").style.display = "none";
    document.querySelector(".noconnection").style.display = "none";
    if (winner == 1) {
        document.querySelector(".wongame").style.display = "initial";
        winner = 0;
    }
    if (winner == 2) {
        document.querySelector(".lostgame").style.display = "initial";
        winner = 0;
    }
    for (var i = 0; i < cells.length; i++) {
        if (gameboard[i] == 1) {
            cells[i].style.backgroundColor = "white";
        } else {
            cells[i].style.backgroundColor = "black";
        }
        if (possible_moves[i] == 1) {

            cells[i].style.backgroundColor = "yellow";
            cells[i].addEventListener('click', turnClick, false);
        }
    }
    console.log(i);
    player1.playerCir.style.backgroundColor = "green";
    move(cells[player1.actCell], player1);
    player2.playerCir.style.backgroundColor = "red";
    move(cells[player2.actCell], player2);

    test();
}

/**
 * Funkcja wysyła do serwera wiadomość o wymaganym resecie gry.
 */
function reset() {
    var obj = {position: 0, difficulty: difficulty, reset: 1};
    ws.send(JSON.stringify(obj));
}

/**
 * Funkcja otwiera oknienko z wyborem poziomu trudności.
 */
function newGame() {
    document.querySelector(".endgame").style.display = "initial";
}

/**
 * Funkcja zamyka okno z informacją o wygranej lub przegranej.
 */
function ok() {
    document.querySelector(".wongame").style.display = "none";
    document.querySelector(".lostgame").style.display = "none";
}

/**
 * Funkcja odpowiedzialna za ustawienie nowego poziomu trudności oraz ponowne zainicjowanie gry z nowym poziomem.
 * @param d - wybrana trudność gry
 */
function changeDifficulty(d) {
    this.difficulty = d;
    console.log(this.difficulty);
    reset();
}

/**
 * Funkcja uruchamia się w momencie kliknięcia przez gracza w komórke na planszy. Jeśli komórka była aktywna, to informacja
 * o kliknięciu wysyłana jest do serwera.
 * @param square - komórka jaka została kliknięta
 */
function turnClick(square) {
    var position = parseInt(square.target.id);
    if (possible_moves[position] == 1) {
        var obj = {position: parseInt(square.target.id), difficulty: difficulty, reset: 0};
        console.log(obj);
        ws.send(JSON.stringify(obj));
    }
}

/**
 * Funkcja odpowiedzialna za zmiane pozycji gracza.
 * @param cell - komórka na którą gracz zmienia pozycje
 * @param player - gracz, który porusza się
 */
function move(cell, player) {
    var rect = cell.getBoundingClientRect();
    player.playerCir.style.top = rect.top + 2 + "px";
    player.playerCir.style.left = rect.left + 2 + "px";
    player.actCell = cell.id;
}

/**
 * W przypadku zmiany rozmiaru okna funkcja akutalizuje pozycję graczy.
 * @param event
 */
window.onresize = function (event) {
    move(cells[player1.actCell], player1);
    move(cells[player2.actCell], player2);
};

/**
 * Funkcja symulująca rozgrywkę.
 */
function test() {
    var r = 0;
    var p = 0;
    for (var i = 0; i < 49; i++) {
        if (possible_moves[i] == 1) {
            p = i;
            break;
        }
        if (i == 48) {
            r = 1;
        }
    }
    var obj = {position: p, difficulty: difficulty, reset: r};
    console.log(obj);
    setTimeout(function () {
        ws.send(JSON.stringify(obj));
    }, 500);
}
