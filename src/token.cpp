#include "token.hpp"
#include "cstring" 

const char* TYPE_NAMES[] =  {"INTEGER", "ADD_SUB", "MULT_DIV", "WS", "_EOF", "PAR", "BEGIN", "END", "DOT", "ID", "ASSIGN", "SEMI", "ERROR", "NONE"};

/*******************************************************************************
 * Token Implementation 
 ******************************************************************************/
Token::Token(){
    type = NONE;
}

// for tokens without a value (e.g. _EOF)
Token::Token(Type type){
    this->type = type;
}

Token::Token(Type type, int integer){
    this->type = type; 
    value.integer = integer; 
}

Token::Token(Type type, char op){
    this->type = type; 
    value.op = op; 
}

Token::Token(Type type, const char* id){
    this->type = type; 
    strncpy(value.identifier, id, sizeof(value.identifier)); // no null term if s > d  
}

Value Token::get_value(){
    return value; 
}

Type Token::get_type(){
    return type; 
}

// check if this token is the expected type 
bool Token::is_type(Type t){
    return this->type == t; 
}

int Token::get_int(){
    return value.integer; 
}

