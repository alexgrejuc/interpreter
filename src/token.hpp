#ifndef TOKEN_HPP
#define TOKEN_HPP 

#define MAX_ID_LEN 255 // g++ supports indefinite length identifiers ... why ?? 
#define TEMP_MAX_STR 2048 // will remove this limitation 

// the valid types which can be interpreted
// note that NONE is never used aside from the default constructor
// TYPE_SIZE is not a token but a value which tracks the number of enums in Type 
enum Type{INTEGER, ADD_SUB, MULT_DIV, WS, _EOF, PAR, BEGIN, END, DOT, ID, ASSIGN, SEMI, ERROR, NONE};   
extern const char* TYPE_NAMES[];  

// a value in the language can either be an integer or an operator 
union Value{
    int integer; 
    char op;
    char identifier[MAX_ID_LEN + 1];
    char str[TEMP_MAX_STR];  
};

// a token, i.e. the smallest interpretable unit of the text 
// a token has a type (e.g. integer) and often a value (e.g. 16)
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
