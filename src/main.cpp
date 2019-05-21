#include "lexer.hpp"
#include "parser.hpp"
#include "node_visitor.hpp"  
#include <iostream> 

using std::cin; 
using std::cout; 
using std::cerr; 
using std::endl; 

/* prompts user for calculator expressions and then uses an Parser
 * to evaluate them */ 
int main(int argc, char* argv[]){
    //Interpreter calc(""); 
	string text; 

    while(1){
        cout << "calc> "; 
        getline(cin, text); 

        if(text == "" || text == "q" || text == "How to quit vim??") break; 
        
        //calc = Interpreter(text);  
		Interpreter calc = Interpreter(text); 

        // evaluate if expression is well-formed, print error otherwise 
        try {
            int result = calc.interpret(); 
            cout << result << endl; 
			//calc.display();
			cout << endl; 

        } catch(const char *msg){
            cerr << msg << endl; 
        }
    }
}
