#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp" 
#include <string> 
#include <map> 

using std::string; 
using std::map; 

/* lexical analysis: tokenizes the input string */ 
class Lexer{
    private: 
        string text; 
        unsigned int pos; 
        Token current_token;
        
        map<string, Token> reserved_keywords;     
        void reserve_keywords(); 

        char peek(); 
        Token identify(); 
    
    public: 
        Lexer();
        Lexer(string text);

        // returns non-whitespace token or EOF token from text  
        Token get_next_token();
};

#endif 
