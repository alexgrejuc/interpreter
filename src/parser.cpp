/*******************************************************************************
 * Parser Implementation 
 ******************************************************************************/

#include "parser.hpp" 

// consumes/eats the token and grabs the next one if it is of correct type
// otherwise there is an error in the expression so we throw an error
void Parser::eat(Type token_type){
    if(current_token.is_type(token_type)) 
        current_token = lexer.get_next_token(); 
    else
        throw "error eating token";  
}

// consumes/eats the token and grabs the next one if it is of correct type & val
// otherwise there is an error in the expression so we throw an error
void Parser::eat(Type token_type, char val){
    if(current_token.is_type(token_type) && current_token.get_value().op == val) 
        current_token = lexer.get_next_token(); 
    else
        throw "error eating token";  
}

// parses a parenthesis-containing expression  
AST* Parser::par(){
    //Token par = current_token; 
    
    eat(PAR, '('); 
    //par = Token(INTEGER, expr().integer);  
    AST* par = expr(); 
    //AST* par = new Num(expr()->get_token()); 
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
    Token result = current_token; 

    if(result.get_type() == PAR) return par(); 
	else if(result.get_type() == ADD_SUB) return unary();
	else return number(); 
    
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
AST* Parser::expr(){
    AST* left = term();  

    while(current_token.get_type() == ADD_SUB){
        Token op = add_sub(); 
        left = new BinOp(left, op, term());
    }

    return left; 
}

AST* Parser::parse(){
    return expr(); 
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
    lexer = Lexer("");
    current_token = lexer.get_next_token();   
} 
