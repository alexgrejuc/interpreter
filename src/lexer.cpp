/*******************************************************************************
 * Lexer Implementation 
 ******************************************************************************/

#include "lexer.hpp" 
#include "utilities.hpp"
#include <string.h>
#include <ctype.h> 
#include <iostream> 

using std::cout; 
using std::endl; 
using std::string; 

#define OVERFLOW '~' // a dirty way for peek() to indicate it has gone out of bounds  

Lexer::Lexer(){
    Lexer(string("")); 
}

Lexer::Lexer(string text){
    pos = 0; 
    this->text = text;
    reserve_keywords(); 
}

char Lexer::peek(){
    unsigned int peek_pos = pos + 1; 
    return (peek_pos >= text.length()) ? OVERFLOW : text[peek_pos]; 
}

Token Lexer::identify(){
    char name[TEMP_MAX_STR + 1], lower_name[TEMP_MAX_STR + 1];
    int name_pos = 0; 

    while(pos < text.length() && is_alphanumeric(text[pos])){
        if(name_pos < TEMP_MAX_STR){
            name[name_pos++] = text[pos++];
        }
        else {
            break; 
        }
    }

    name[name_pos] = '\0'; 
    strcpy(lower_name, name);
    
    if(name_pos < TEMP_MAX_STR){
        to_lower(lower_name);  
        
        if(reserved_keywords.find(lower_name) != reserved_keywords.end()){
            return reserved_keywords[lower_name]; 
        }
        else {
            return Token(ID, name); 
        }
    }

    cout << "Identifer " << name << " exceeds the maximum length of " << TEMP_MAX_STR << endl; 
    return Token(ERROR); 
}

void Lexer::reserve_keywords(){
    reserved_keywords["begin"] = Token(BEGIN, "BEGIN"); 
    reserved_keywords["end"] = Token(END, "END"); 
}

// returns non-whitespace token or EOF token from text  
Token Lexer::get_next_token(){

    if(pos >= text.length()) return Token(_EOF); 

    char current_char = text[pos]; 

    // consumes whitespace 
    if(is_ws(current_char)){
        pos++; 
        return get_next_token();    // recursive call so we return a non-ws token 
    }

    // return a number token 
    if (is_integer(current_char)){
        int start = pos; 
        while(is_integer(text[pos])) pos++;                     // count up all the adjacent digits  

        int num = str_to_int(text.substr(start, pos - start));  // integerize the string 

        Token integer(INTEGER, num); 
        return integer; 
    }

    if(current_char == '*'){
        Token op = Token(MULT, current_char, MULT_DIV_K);
        pos++; 
        return op;  
    }

    if(current_char == '/'){
        Token op = Token(DIV, current_char, MULT_DIV_K);
        pos++; 
        return op;  
    }
    
    // return an add/sub token 
    if(current_char == '+' || current_char == '-') {
        Token op = Token(ADD_SUB, current_char, ADD_SUB_K);
        pos++; 
        return op;  
    }

    // return a parenthesis token 
    if(current_char == '(' || current_char == ')'){
        Token par = Token(PAR, current_char);
        pos++;
        return par;  
    }

    if(is_letter(current_char)){
        return identify(); 
    }

    if(current_char == ':' && peek() == '='){
        pos+= 2;
        return Token(ASSIGN, ":=");
    }
    
    if(current_char == ';'){
        pos++; 
        return Token(SEMI, current_char);
    }

    if(current_char == '.'){
        Token dot = Token(DOT, current_char);
        pos++; 
        return dot; 
    }

    return Token(_EOF);
}
