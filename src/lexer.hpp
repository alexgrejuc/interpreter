#ifndef LEXER_HPP
#define LEXER_HPP

#include <string> 
#include "token.hpp" 
#include <map> 

using std::string; 
using std::map; 

/* tokenizes the input string and returns either numerical, operand, or EOF tokens */ 
class Lexer{
    private: 
        string text; 
        unsigned int pos; 
        Token current_token;
        
        map<string, Token> reserved_keywords;     
        
        int to_int(char c);
        bool is_ws(char c);
        bool is_integer(char c);
        bool is_letter(char c); 
        bool is_alphanumeric(char c);

        // converts a string to an integer by summing (integer * place value) for all chars 
        int str_to_int(string literal);
        
        char peek(); 
        Token identify(); 

        void reserve_keywords(); 

    public: 
        Lexer();
        Lexer(string text);

        // returns non-whitespace token or EOF token from text  
        Token get_next_token();
};

#endif 
