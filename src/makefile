CXXFLAGS = -Wall -std=c++11 -g 
TESTFLAGS = -Wall -std=c++11 -o test-calc.out  

make: parser.o lexer.o node_visitor.o token.o ast.o main.cpp
	g++ main.cpp parser.o lexer.o node_visitor.o ast.o token.o -o calculator.out $(CXXFLAGS)

parser.o: parser.hpp parser.cpp ast.o 
	g++ -c parser.cpp ast.o token.o $(CXXFLAGS) 

lexer.o: lexer.hpp lexer.cpp ast.o 
	g++ -c lexer.cpp ast.o token.o $(CXXFLAGS) 

node_visitor.o: node_visitor.hpp node_visitor.cpp
	g++ -c node_visitor.cpp 

ast.o: ast.hpp ast.cpp token.o  
	g++ -c ast.cpp token.o $(CXXFLAGS) 

token.o: token.hpp token.cpp  
	g++ -c token.cpp $(CXXFLAGS) 

tests: test_calculator.cpp  
	g++ test_calculator.cpp parser.o lexer.o node_visitor.o $(TESTFLAGS) 

clean:
	rm *.out *.o  
