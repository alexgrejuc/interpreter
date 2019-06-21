#ifndef NODEVISITOR_HPP
#define NODEVISITOR_HPP

#include "token.hpp" 
#include <string>
#include "parser.hpp" 

using std::string; 

class AST; 
class BinOp; 
class UnOp ;
class Num; 

class NodeVisitor{
	protected:
        Parser parser;
        AST* ast;
    public:
        NodeVisitor(string text); 
        virtual Value visit(Compound* n) = 0; 
        virtual Value visit(Variable* n) = 0; 
        virtual Value visit(Assignment* n) = 0; 
        virtual Value visit(NoOp* n) = 0;  
		virtual Value visit(BinOp*) = 0; 
        virtual Value visit(Num*) = 0;
		virtual Value visit(UnOp*) = 0; 
		virtual void display() = 0;  
};

typedef std::map<string, Value> SymbolTable; 

class Interpreter : NodeVisitor{
    private:
        SymbolTable symbol_table; // Just a global scope for now, lots of work to be done later;      
    public: 
        Value visit(Compound* n);
        Value visit(Variable* n); 
        Value visit(Assignment* n);
        Value visit(NoOp* n); 
        Value visit(BinOp* n); 
        Value visit(UnOp* n); 
		Value visit(Num* n); 

        Interpreter(string text);
        void display_symbols(); 
        void display();
		void interpret(); 
        int interpret(string text); 
        int node_visitor();   
}; 

/*
worked before the pascal-like features were added -- too tedious to maintain so I nixed it 
class VisitorRPN : NodeVisitor{
	public:
		VisitorRPN(string text); 
		void display();  
        Value visit(Compound* n);
        Value visit(Variable* n); 
        Value visit(Assignment* n);
        Value visit(NoOp* n); 
		Value visit(BinOp*);
		Value visit(UnOp*);
		Value visit(Num*); 
}; 

class VisitorLisp : NodeVisitor{
	public:
		VisitorLisp(string text); 
		void display(); 
        Value visit(Compound* n);
        Value visit(Variable* n); 
        Value visit(Assignment* n);
        Value visit(NoOp* n); 
		Value visit(UnOp*);  
		Value visit(BinOp*);
		Value visit(Num*); 
};
*/ 
#endif 
