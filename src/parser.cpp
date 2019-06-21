/*******************************************************************************
 * Parser Implementation 
 ******************************************************************************/

#include "parser.hpp" 
#include <iostream>

using namespace std; 
using std::list; 
using std::cerr; 

// consumes/eats the token and grabs the next one if it is of correct type
// otherwise there is an error in the expression so we throw an error
void Parser::eat(Type token_type){
    if(current_token.is_type(token_type)) 
        current_token = lexer.get_next_token(); 
    else{
        cerr << "Expected " << TYPE_NAMES[token_type] << " but got " << TYPE_NAMES[current_token.get_type()] << endl; 
        throw "error eating token";  
    }
}

// consumes/eats the token and grabs the next one if it is of correct type & val
// otherwise there is an error in the expression so we throw an error
void Parser::eat(Type token_type, char val){
    if(current_token.is_type(token_type) && current_token.get_value().op == val) 
        current_token = lexer.get_next_token(); 
    else{
        cerr << "Expected " << token_type << " with value " << val << " but got " << current_token.get_type() << " with value " << current_token.get_value().op << endl; 
        throw "error eating token";  
    }
}

AST* Parser::program(){
    AST* tree = compound_statement(); 
    eat(DOT); 
    return tree; 
}

AST* Parser::compound_statement(){
    eat(BEGIN);
    Nodes statements = statement_list();  
    eat(END); 
    return new Compound(statements); 
}

Nodes Parser::statement_list(){
    AST* s = statement(); 

    Nodes statements(1, s); 

    while(current_token.get_type() == SEMI){
        eat(SEMI); 
        statements.push_back(statement()); 
    }

    if(current_token.get_type() == ID) throw "Unexpected assignment. Did you forget a ; ?";

    return statements; 
}

AST* Parser::statement(){
    AST* node; 
    Type t = current_token.get_type(); 

    if(t == BEGIN) node = compound_statement();
    else if (t == ID) node = assignment();
    else node = empty();

    return node; 
}

AST* Parser::assignment(){
    Variable* left = variable();
    eat(ASSIGN); 
    return new Assignment(left, expression()); 
}

Variable* Parser::variable(){
    Variable* var = new Variable(current_token); 
    eat(ID); 
    return var; 
}

AST* Parser::empty(){
    return new NoOp(); 
}

// parses a parenthesis-containing expression  
AST* Parser::par(){
    eat(PAR, '('); 
    AST* par = expression(); 
    eat(PAR, ')');

    return par; 
    //return par.get_value(); 
}

// parses a number (just ints for now, floats to come?)
AST* Parser::number(){
    Token number = current_token; 
    eat(INTEGER); 
    return new Num(number); 
}

AST* Parser::unary(){
	Token operand = add_sub();
	return new UnOp(operand, factor());   
}

// parses a "factor" i.e. integers or parenthetical expressions   
AST* Parser::factor(){
    Type t = current_token.get_type(); 

    if(t == PAR) return par(); 
	else if(t == ADD_SUB) return unary();
	else if(t == INTEGER) return number();
    else return variable();  
}

// eats a *,/ operand and returns its value
Token Parser::mult_div(){
    Token operand = current_token; 
    eat(MULT_DIV);
    return operand; 
}

// eats a +,- operand and returns its value
Token Parser::add_sub(){
    Token operand = current_token; 
    eat(ADD_SUB);
    return operand; 
}

// parses 3-groups of tokens into a mult/div expression
// accumulates their evaluated result in the left value 
AST* Parser::term(){
    AST* left = factor();  

    while(current_token.get_type() == MULT_DIV){
        Token op = mult_div();
        left = new BinOp(left, op, factor()); 
    }

    return left; 
}

// parses 3-groups of tokens into an add/sub expression
// accumulates their evaluated result in the left value 
AST* Parser::expression(){
    AST* left = term();  

    while(current_token.get_type() == ADD_SUB){
        Token op = add_sub(); 
        left = new BinOp(left, op, term());
    }

    return left; 
}

AST* Parser::parse(){
    return program(); 
}

// evaluates a binary artihmetic expression 
int Parser::eval(Value l, Value r, Value operand){
    switch(operand.op){
        case('+'): return l.integer + r.integer;
        case('-'): return l.integer - r.integer;
        case('*'): return l.integer * r.integer; 
        case('/'): return l.integer / r.integer; 
        default: 
            throw "Undefined operation"; 
            return 0; 
    }
}

Parser::Parser(string text){
    lexer = Lexer(text);
    current_token = lexer.get_next_token();   
}


Parser::Parser(){     
    //lexer(); 
    lexer = Lexer();
    //current_token = lexer.get_next_token();   
} 
