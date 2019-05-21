#ifndef AST_HPP
#define AST_HPP 

#include "token.hpp"

class NodeVisitor; 

class AST{
    protected:
        Token token;
    public:
        Token get_token(); 
        Value get_value(); 
        Type get_type();
        virtual Value accept(NodeVisitor*) = 0;   
}; 

class BinOp : public AST{
    private:
    public:
        AST* left; 
        AST* right;
        BinOp(); 
        BinOp(AST*, Token, AST*); 
        Value accept(NodeVisitor*); 
};

class UnOp : public AST{
	private: 
	public:
		AST* operand;
		UnOp(Token, AST*);
		Value accept(NodeVisitor*);  
};

class Num : public AST{
    public:
        Num();
        Num(Token);
        Value accept(NodeVisitor*); 
};

#endif 
