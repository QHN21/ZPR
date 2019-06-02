#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "..\Game.h"
#include "..\AI.h"
#include "..\Player.h"
#include "..\Board.h"
#include "..\Square.h"
#include "..\GamesHandler.h"
#include <iostream>
TEST_CASE( "Square Tested", "[Square]" ) {
    Square s(1,1);
    REQUIRE( s.getFree() == 1 );
    REQUIRE( s.getPosition()[0] == 1);
    REQUIRE( s.getPosition()[1] == 1);

    SECTION("Changing his occupation from free to occupied and back"){
      s.setFree(false);
      REQUIRE( s.getFree() == 0 );
      s.setFree(true);
      REQUIRE( s.getFree() == 1 );
    }

    SECTION("Setting different Square positions"){
      for(int i = 0; i<7; i++){
        for(int j = 0; j < 7; j++){
            Square s(i,j);
            REQUIRE( s.getPosition()[0] == i);
            REQUIRE( s.getPosition()[1] == j);
        }
      }
    }
}

TEST_CASE( "Board Tested", "[Board]" ){
  Board b;
  SECTION("isLegal testing"){
    for(int i = 0; i<7; i++){
      for(int j = 0; j < 7; j++){
          REQUIRE( b.isLegal(i,j) == true);
          REQUIRE( b.isLegal(i,j) == true);
      }
    }
  }
  SECTION("getSquares testing"){
    for(int i = 0; i<7; i++){
      for(int j = 0; j < 7; j++){
          REQUIRE( (b.getSquares()[i*7+j]->getPosition()[0]) == i);
          REQUIRE( (b.getSquares()[i*7+j]->getPosition()[1]) == j);
      }
    }
  }

  SECTION("getFreeSquares testing"){
    for(int i = 0; i<7; i++){
      for(int j = 0; j < 7; j++){
          REQUIRE( (b.getFreeSquares()[i*7+j][0]) == i);
          REQUIRE( (b.getFreeSquares()[i*7+j][1]) == j);
      }
    }
  }
  SECTION("Square modification testing"){
    b.getSquares()[0] -> setFree(false);
    REQUIRE( b.isLegal(0,0) == false);
    b.getSquares()[0] -> setFree(true);
    REQUIRE( b.isLegal(0,0) == true);
  }

}


TEST_CASE( "Player Tested", "[Player]" ){
    std::shared_ptr<Board> b = std::make_shared<Board>();
    Player p(b,0,0);
    REQUIRE( p.getPosition()[0] == 0);
    REQUIRE( p.getPosition()[1] == 0);
    REQUIRE( b->isLegal(0,0) == false);


    SECTION("Player possibleMoves testing"){
        REQUIRE(p.possibleMoves()[0][0] == 0);
        REQUIRE(p.possibleMoves()[0][1] == 1);
    }

    SECTION("Player move testing"){
      p.move(1,0);
      REQUIRE( p.getPosition()[0] == 1);
      REQUIRE( p.getPosition()[1] == 0);
      REQUIRE( b->isLegal(1,0) == false);
    }


    SECTION("Player hide square testing"){
      p.hideSquare(2,2);
      REQUIRE( b->isLegal(2,2) == false);
    }

    SECTION("Player reset testing"){
      p.hideSquare(6,6);
      REQUIRE( b->isLegal(6,6) == false);
    }

}

TEST_CASE( "AI Tested", "[AI]" ){
    std::shared_ptr<Board> b = std::make_shared<Board>();
    Player* player1 = new Player(b,3,6);
    Player* player2 = new Player(b,3,0);
    AI ai(b);
    int *position = ai.minmax(player2->getPosition(), player1->getPosition(), 2, -1000000, 1000000, b->getFreeSquares());
    REQUIRE(position[0] == 2);
    REQUIRE(position[1] == 1);
    REQUIRE(position[2] == 3);
    REQUIRE(position[3] == 4);
}

TEST_CASE( "Game Tested", "[Game]" ){
  Game g(1,2);
  REQUIRE(g.getID() == 1);
  REQUIRE(g.getGameState()[0] == '{');
  REQUIRE(g.move(1,1)[0] == '{');
  REQUIRE(g.resetGame(3)[0] == '{');
}

TEST_CASE( "GamesHandler Tested", "[GamesHandler]" ){
  GamesHandler g=GamesHandler::getInstance();
  g.addNewGame(1,1);
  REQUIRE(g.gameState(1)[0] == '{');
  REQUIRE(g.move(1,1)[0] == '{');
  REQUIRE(g.resetGame(1,2)[0] == '{');
}
