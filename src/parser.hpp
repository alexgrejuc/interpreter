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
 * arithmetic precedence 
 * parenthesis
 * mult/div
 * add/sub 
 * 
 * The Grammar: 
 * terminals are uppercase and nonterminals are lowercase 
 * 
 * program: compound_statement DOT
 *
 * compound_statement: BEGIN statement_list END
 *
 * statement_list: statement 
 *               | statement SEMI statement_list 
 *
 * statement: compound_statement 
 *          | assignment 
            | empty 
 *
 * assignment: variable ASSIGN expression 
 *
 * expression: term(ADD_SUB term)*
 *
 * term: factor(MULT_DIV factor)*  
 *
 * factor: INTEGER 
 *       | (ADD_SUB)factor 
 *       | par
 *
 * par: (expression expression*)    
 *
 * empty: 
 * variable: [a-z]*[0-9|a-Z]* // not the actual regex but you get the idea...
 ******************************************************************************/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "ast.hpp"
#include "token.hpp"
#include "lexer.hpp" 
#include <list> 

/* interprets the value of a calculator expression and returns its value
 * uses the lexer to tokenize the string, parses tokens
 * and calculates the result of the expression */ 
class Parser{
    private:
        Token current_token;
        Lexer lexer;  

        // prints a somewhat informative parse error message and throws and exception 
        void parse_error(Kind acceptable, Type actual);
        void parse_error(Type acceptable, Type actual); 

        // consumes/eats the token and grabs the next one if it is of correct type
        // otherwise there is an error in the expression so we throw an error
        void eat(Type token_type);
        void eat(Type token_type, char val);
        
        void eat_multdiv(); 

        // functions to parse the rules specified in the above grammar 
        AST* program(); 
        AST* compound_statement(); 
        Nodes statement_list();
        Variable* variable();
        AST* statement(); 
        AST* assignment();
        AST* empty(); 
        
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
        AST* expression();

        // evaluates a binary artihmetic expression 
        int eval(Value l, Value r, Value operand);
    public:
        Parser(string text);
        Parser(); 

        AST* parse(); 
};

#endif
