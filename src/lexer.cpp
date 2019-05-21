/*******************************************************************************
 * Lexer Implementation 
 ******************************************************************************/

#include "lexer.hpp" 
#include <math.h> 

int Lexer::to_int(char c){
    return c - '0'; 
}

bool Lexer::is_ws(char c){
    return c == ' ' || c == '\n' || c == '\t'; 
}

bool Lexer::is_integer(char c){
    return (c >= '0' && c <= '9'); 
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

Lexer::Lexer(){
    pos = 0; 
    text = "";  
}

Lexer::Lexer(string text){
    pos = 0; 
    this->text = text; 
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
    
    return Token(_EOF);
}
