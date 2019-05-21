#include "token.hpp"

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

Token::Token(Type type, int value){
    this->type = type; 
    this->value.integer = value; 
}

Token::Token(Type type, char value){
    this->type = type; 
    this->value.op = value; 
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