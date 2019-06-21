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

typedef std::list<AST*> Nodes;
typedef Nodes::const_iterator NodesConstIterator; 

class Compound : public AST{
    private:
        std::list<AST*> children;
    public:

        NodesConstIterator begin() { return children.begin(); }
        NodesConstIterator end() { return children.end(); }

        Compound(std::list<AST*> children);
        Value accept(NodeVisitor*); 
        void add_child(AST* child);  
};

class Variable : public AST{
    public:
        Variable(Token token); 
        const char* get_name();
        Value accept(NodeVisitor*); 
};

class Assignment: public AST{
    private:
        Variable* left; 
    public:
        AST* right; 
        const char* get_name();
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
