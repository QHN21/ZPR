#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "..\Game.h"
#include "..\AI.h"
#include "..\Player.h"
#include "..\Board.h"
#include "..\Square.h"
#include "..\GamesHandler.h"

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
    std::shared_ptr<Board> board = std::make_shared<Board>();
    Player p(board,0,0);
    REQUIRE( p.getPosition()[0] == 0);
    REQUIRE( p.getPosition()[1] == 0);
}

TEST_CASE( "AI Tested", "[AI]" ){

}

TEST_CASE( "Game Tested", "[Game]" ){

}

TEST_CASE( "GamesHandler Tested", "[GamesHandler]" ){

}
