#include "lexer.hpp"
#include "parser.hpp"
#include "string.h" 
#include "node_visitor.hpp"  
#include <iostream> 
#include <iterator> 
#include <string> 

using std::cin; 
using std::cout; 
using std::cerr; 
using std::endl; 

bool run(string text){
    if(text == "" || text == "q" || text == "How to quit vim??") return false; 

    //calc = Interpreter(text);  
    Interpreter interpreter = Interpreter(text); 

    // evaluate if expression is well-formed, print error otherwise 
    try {
        interpreter.display(); 
        cout << endl; 

    } catch(const char *msg){
        cerr << msg << endl; 
    }

    return true; 
}

/* prompts user for calculator expressions and then uses an Parser
 * to evaluate them */ 
int main(int argc, char* argv[]){
    string text; 
    
    if(argc == 1){
        // can take in a program from a file if stdin is redirected 
        // can also type out a program using newlines for formatting 
        // send EOF with Ctrl+D when doing so 
        std::istreambuf_iterator<char> begin(std::cin), end;
        text = string(begin, end);
       
        run(text); 
    }
    else if(argc == 2 && !strcmp(argv[1], "-i")){
        // interactive mode: takes input line-by-line and interprets it. 
        do{
            cout << "> "; 
            getline(cin, text); 
        } while(run(text)); 
    }
}
