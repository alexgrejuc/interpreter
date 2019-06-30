#include "utilities.hpp" 
#include <string.h> 
#include <math.h> 

void to_lower(char* str){
    int i = 0; 
    int delta = 'a' - 'A'; 

    while(str[i] != '\0'){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + delta;  
        }
        
        i++; 
    }
}

char* make_lower(const char* str){
    char* lower = (char*) malloc(sizeof(char) * strlen(str)); 
    strcpy(lower, str); 
    to_lower(lower); 
    return lower;    
}

int to_int(char c){
    return c - '0'; 
}

bool is_ws(char c){
    return c == ' ' || c == '\n' || c == '\t'; 
}

bool is_integer(char c){
    return (c >= '0' && c <= '9'); 
}

bool is_letter(char c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool is_alphanumeric(char c){
   return (is_letter(c) || (c >= '0' && c <= '9')); 
}

// converts a string to an integer by summing (integer * place value) for all chars 
int str_to_int(string literal){
    int num = 0; 
    int place = 0; 

    // sum one's place...n's place 
    for(int i = literal.size() - 1; i >= 0; i--){
        num+= to_int(literal[i]) * pow(10, place++); 
    }

    return num; 
}
