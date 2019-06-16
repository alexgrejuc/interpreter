/*******************************************************************************
 * Lexer Implementation 
 ******************************************************************************/

#include "lexer.hpp" 
#include <math.h> 
#include <string.h>
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

int Lexer::to_int(char c){
    return c - '0'; 
}

bool Lexer::is_ws(char c){
    return c == ' ' || c == '\n' || c == '\t'; 
}

bool Lexer::is_integer(char c){
    return (c >= '0' && c <= '9'); 
}

bool Lexer::is_letter(char c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool Lexer::is_alphanumeric(char c){
   return (is_letter(c) || (c >= '0' && c <= '9')); 
}

// converts a string to an integer by summing (integer * place value) for all chars 
int Lexer::str_to_int(string literal){
    int num = 0; 
    int place = 0; 

    // sum one's place...n's place 
    for(int i = literal.size() - 1; i >= 0; i--){
        num+= to_int(literal[i]) * pow(10, place++); 
    }

    return num; 
}

char Lexer::peek(){
    unsigned int peek_pos = pos + 1; 
    return (peek_pos >= text.length()) ? OVERFLOW : text[peek_pos]; 
}

Token Lexer::identify(){
    char name[MAX_ID_LEN + 1];
    int name_pos = 0; 

    while(pos < text.length() && is_alphanumeric(text[pos])){
        if(name_pos < MAX_ID_LEN){
            name[name_pos++] = text[pos++];
        }
        else {
            break; 
        }
    }

    name[name_pos] = '\0'; 
    
    if(name_pos < MAX_ID_LEN){
        if(reserved_keywords.find(name) != reserved_keywords.end()){
            return reserved_keywords[name]; 
        }
        else {
            return Token(ID, name); 
        }
    }

    cout << "Identifer " << name << " exceeds the maximum length of " << MAX_ID_LEN << endl; 
    return Token(ERROR); 
}

void Lexer::reserve_keywords(){
    reserved_keywords["BEGIN"] = Token(BEGIN, "BEGIN"); 
    reserved_keywords["END"] = Token(END, "END"); 
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

    // return an mult/div token 
    if(current_char == '*' || current_char == '/'){
        Token op = Token(MULT_DIV, current_char);
        pos++; 
        return op;  
    }

    // return an add/sub token 
    if(current_char == '+' || current_char == '-') {
        Token op = Token(ADD_SUB, current_char);
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
