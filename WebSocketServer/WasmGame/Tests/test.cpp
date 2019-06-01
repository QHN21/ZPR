#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
//#include "..\Game.h"
//#include "..\AI.h"
//#include "..\Player.h"
//#include "..\Board.h"
#include "..\Square.h"

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
