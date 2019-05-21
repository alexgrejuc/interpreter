#ifndef TOKEN_HPP
#define TOKEN_HPP 

// the valid types which can be interpreted
// note that NONE is never used aside from the default constructor 
enum Type{INTEGER, ADD_SUB, MULT_DIV, WS, _EOF, PAR, NONE}; 

// a value in the language can either be an integer or an operator 
union Value{
    int integer; 
    char op; 
};

// a token, i.e. the smallest interpretable unit of the text 
// a token has a type (e.g. integer) and a value (e.g. 16)
class Token{
    private:
        Type type; 
        Value value; 

    public:
    
    Token();

    // for tokens without a value (e.g. _EOF)
    Token(Type type);

    Token(Type type, int value);

    Token(Type type, char value);

    Value get_value();

    Type get_type();

    // check if this token is the expected type 
    bool is_type(Type t);

    int get_int();
};

#endif 