#ifndef LEXER_HPP
#define LEXER_HPP

#include <string> 
#include "token.hpp" 
using std::string; 

/* tokenizes the input string and returns either numerical, operand, or EOF tokens */ 
class Lexer{
    private: 
        string text; 
        unsigned int pos; 
        Token current_token;

        int to_int(char c);

        bool is_ws(char c);

        bool is_integer(char c);

        // converts a string to an integer by summing (integer * place value) for all chars 
        int str_to_int(string literal);

    public: 
        Lexer();

        Lexer(string text);

        // returns non-whitespace token or EOF token from text  
        Token get_next_token();
};

#endif 
