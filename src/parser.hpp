/*******************************************************************************
 * My first foray into learning about translators (i.e. Parsers & compilers)
 * 
 * A calculator which evaluates arithmetic expressions with recursive descent 
 * 
 * v2:
 *    Evaluates expressions containing positive integers, (), and +,-,*,/ 
 *    Evaluates left to right with precedence
 *    
 * 
 * Written by Alex Grejuc
 * Based off of Ruslan Spivak's tutorials (thanks!)
 * https://ruslanspivak.com/lsbasi-part1/ 
 * 
 * precedence: 
 * parenthesis
 * mult/div
 * add/sub 
 * 
 * expr: term(ADD_SUB term)*
 * term: factor(MULT_DIV factor)*  
 * factor: INTEGER | (ADD_SUB)factor | par
 * par: (expr expr*)    
 ******************************************************************************/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "ast.hpp"
#include "token.hpp"
#include "lexer.hpp" 

/* interprets the value of a calculator expression and returns its value
 * uses the lexer to tokenize the string, parses tokens
 * and calculates the result of the expression */ 
class Parser{
    private:
        Token current_token;
        Lexer lexer;  

        // consumes/eats the token and grabs the next one if it is of correct type
        // otherwise there is an error in the expression so we throw an error
        void eat(Type token_type);

        // consumes/eats the token and grabs the next one if it is of correct type & val
        // otherwise there is an error in the expression so we throw an error
        void eat(Type token_type, char val);

        // parses a parenthesis-containing expression  
        AST* par();

        // parses a number (just ints for now, floats to come?)
        AST* number();

		// parses a unary operator node 
		AST* unary();

        // parses a "factor" i.e. integers or parenthetical expressions   
        AST* factor();

        // eats a *,/ operand and returns its AST*
        Token mult_div();

        // eats a +,- operand and returns its AST*
        Token add_sub();

        // parses 3-groups of tokens into a mult/div expression
        // accumulates their evaluated result in the left AST* 
        AST* term();

        // parses 3-groups of tokens into an add/sub expression
        // accumulates their evaluated result in the left value
        AST* expr();

        // evaluates a binary artihmetic expression 
        int eval(Value l, Value r, Value operand);
    public:
        Parser(string text);
        Parser(); 

        AST* parse(); 
};

#endif
