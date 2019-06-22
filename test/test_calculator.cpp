/*******************************************************************************
 * Very simple tests because I wanted to learn about a C++ test framework    
 ******************************************************************************/

#define CATCH_CONFIG_MAIN // tells catch to provide a main() -- should only be done in one .cpp file  
#include "catch.hpp"
#include "node_visitor.hpp" 

TEST_CASE("Basic expected inputs"){
	Parser calculator(""); 
	
	calculator = Parser("1 + 2"); 
	REQUIRE(calculator.expr().integer == 3); 

	calculator = Parser("0"); 
	REQUIRE(calculator.expr().integer == 0);

	calculator = Parser("2 + 2 - 2 - 2"); 
	REQUIRE(calculator.expr().integer == 0);

	calculator = Parser("1 - 2 * 10"); 
	REQUIRE(calculator.expr().integer == -19);

	calculator = Parser("(1 - 2) * 10"); 
	REQUIRE(calculator.expr().integer == -10);

	calculator = Parser("1 / 3"); 
	REQUIRE(calculator.expr().integer == 0);

	calculator = Parser("2147483647+0"); 
	REQUIRE(calculator.expr().integer == 2147483647);

	calculator = Parser("1111 + 0000 + 0000 + 00000 + (0) + (0-1)"); 
	REQUIRE(calculator.expr().integer == 1110);

	calculator = Parser("(1/1) + (0) + (3 * 2) - 4"); 
	REQUIRE(calculator.expr().integer == 3);
}
