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
		virtual Value visit(BinOp*) = 0; 
        virtual Value visit(Num*) = 0;
		virtual Value visit(UnOp*) = 0; 
		virtual void display() = 0;  
};

class Interpreter : NodeVisitor{
    private:
    public: 
        Value visit(BinOp* n); 
        Value visit(UnOp* n); 
		Value visit(Num* n); 

        Interpreter(string text);
        void display();
		int interpret(); 
        int interpret(string text); 
        int node_visitor();   
}; 

class VisitorRPN : NodeVisitor{
	public:
		VisitorRPN(string text); 
		void display();  
		Value visit(BinOp*);
		Value visit(UnOp*);
		Value visit(Num*); 
}; 

class VisitorLisp : NodeVisitor{
	public:
		VisitorLisp(string text); 
		void display(); 
		Value visit(UnOp*);  
		Value visit(BinOp*);
		Value visit(Num*); 
};

#endif 
