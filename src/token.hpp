#ifndef TOKEN_HPP
#define TOKEN_HPP 

#define TEMP_MAX_STR 2048 // will remove this limitation 

// i.e. the type of a type. Types are of the same Kind if they could be interchanged in a grammar rule  
enum Kind{NUMERIC_K, MULT_DIV_K, ADD_SUB_K, CHARACTERS_K, NONE_K};

// the valid types which can be interpreted
// note that NONE is never used aside from the default constructor
enum Type{INTEGER, ADD_SUB, MULT, DIV, INT_DIV, WS, _EOF, PAR, BEGIN, END, DOT, ID, ASSIGN, SEMI, ERROR, NONE};   

extern const char* TYPE_NAMES[];  
extern const char* KIND_NAMES[]; 

// a value in the language can either be an integer or an operator 
union Value{
    int integer; 
    char op;
    char str[TEMP_MAX_STR];  
};

// a token, i.e. the smallest interpretable unit of the text 
// a token has a type (e.g. integer) and often a value (e.g. 16)
class Token{
    private:
        Type type; 
        Value value; 
        Kind kind; 

    public:
        
    Token();

    Token(Type type, Kind kind = NONE_K); // for tokens without a value (e.g. _EOF)
    Token(Type type, int integer, Kind kind = NUMERIC_K);
    Token(Type type, char op, Kind kind);
    Token(Type type, const char* id, Kind kind = CHARACTERS_K); 

    Value get_value();

    Type get_type();
    Kind get_kind();

    // check if this token is the expected type 
    bool is_type(Type t);

    int get_int();
};

#endif 
