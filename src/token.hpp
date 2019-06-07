#ifndef TOKEN_HPP
#define TOKEN_HPP 

#include <string>
using std::string;

#define MAX_ID_LEN 255 // g++ supports indefinite length identifiers ... why ?? 

// the valid types which can be interpreted
// note that NONE is never used aside from the default constructor 
enum Type{INTEGER, ADD_SUB, MULT_DIV, WS, _EOF, PAR, BEGIN, END, DOT, ID, ASSIGN, SEMI, ERROR, NONE}; 

// a value in the language can either be an integer or an operator 
union Value{
    int integer; 
    char op;
    char identifier[MAX_ID_LEN + 1];  
};

// a token, i.e. the smallest interpretable unit of the text 
// a token has a type (e.g. integer) and a value (e.g. 16)
class Token{
    private:
        Type type; 
        Value value; 

    public:
    
    Token();

    Token(Type type); // for tokens without a value (e.g. _EOF)
    Token(Type type, int integer);
    Token(Type type, char op);
    Token(Type type, const char* id); 

    Value get_value();

    Type get_type();

    // check if this token is the expected type 
    bool is_type(Type t);

    int get_int();
};

#endif 
