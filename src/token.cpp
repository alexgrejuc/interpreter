#include "token.hpp"
#include "cstring" 

const char* TYPE_NAMES[] =  {"INTEGER", "ADD_SUB", "*", "/", "DIV", "WHITESPACE", "_EOF", "PAR", "BEGIN", "END", "DOT", "ID", "ASSIGN", "SEMI", "ERROR", "NONE"};
const char* KIND_NAMES[] = {"NUMERIC", "MULTIPLACTION OR DIVISION", "CHARACTERS", "NO KIND"};

Token::Token(){
    type = NONE;
}

// for tokens without a value (e.g. _EOF)
Token::Token(Type type, Kind kind){
    this->kind = kind; 
    this->type = type;
}

Token::Token(Type type, int integer, Kind kind){
    this->kind = kind; 
    this->type = type; 
    value.integer = integer; 
}

Token::Token(Type type, char op, Kind kind){
    this->kind = kind; 
    this->type = type; 
    value.op = op; 
}

Token::Token(Type type, const char* id, Kind kind){
    this->kind = kind;
    this->type = type; 
    strncpy(value.str, id, sizeof(value.str)); // no null term if s > d  
}

Value Token::get_value(){
    return value; 
}

Type Token::get_type(){
    return type; 
}

Kind Token::get_kind(){
    return kind; 
}

// check if this token is the expected type 
bool Token::is_type(Type t){
    return this->type == t; 
}

int Token::get_int(){
    return value.integer; 
}

