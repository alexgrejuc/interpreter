#ifndef AST_HPP
#define AST_HPP 

#include "token.hpp"
#include <list> 

class NodeVisitor; 

class AST{
    protected:
        Token token;
    public:
        AST(); 
        AST(Token token);
        Token get_token(); 
        Value get_value(); 
        Type get_type();
        virtual Value accept(NodeVisitor*) = 0;   
}; 

class Compound : public AST{
    private:
        std::list<AST*> children;
    public:
        Compound(std::list<AST*> children);
        Value accept(NodeVisitor*); 
        void add_child(AST* child);  
};

class Variable : public AST{
    public:
        Variable(Token token); 
        Value accept(NodeVisitor*); 
};

class Assignment: public AST{
    private:
        Variable* left; 
        AST* right; 
    public:
        Assignment(Variable* left, AST* right); 
        Value accept(NodeVisitor*); 
};

class NoOp : public AST{
    public:
        Value accept(NodeVisitor*); 
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
