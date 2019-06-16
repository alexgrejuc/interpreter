#include "node_visitor.hpp" 
#include "ast.hpp" 
#include <iostream> 

using std::cout; 
using std::endl; 

NodeVisitor::NodeVisitor(string text){
	parser = Parser(text); 
}

Interpreter::Interpreter(string text) : NodeVisitor(text) {}

Value Interpreter::visit(Compound* n){
    Value val;  
    val.integer = 0; 

    return val; 
}

Value Interpreter::visit(Variable* n){
    Value val;
    val.integer = 0; 

    return val; 
}

Value Interpreter::visit(Assignment* n){
    Value val;
    val.integer = 0; 

    return val; 
}

Value Interpreter::visit(NoOp* n){
    Value val;
    val.integer = 0; 

    return val; 
}

Value Interpreter::visit(BinOp* n){
    Value val; 

    if(n->get_value().op == '+'){
        val.integer = n->left->accept(this).integer + n->right->accept(this).integer;     
    }
    else if (n->get_value().op == '-'){
        val.integer = n->left->accept(this).integer - n->right->accept(this).integer;     
    }
    else if (n->get_value().op == '*'){
        val.integer = n->left->accept(this).integer * n->right->accept(this).integer;     
    }
    else {
        val.integer = n->left->accept(this).integer / n->right->accept(this).integer;     
    } 

    return val;    
}

Value Interpreter::visit(UnOp* n){
	Value val; 

	if(n->get_value().op == '+'){
		val.integer = n->operand->accept(this).integer;	
	}
	else if(n->get_value().op == '-'){
		val.integer = -n->operand->accept(this).integer;
	}

	return val; 
}
 
Value Interpreter::visit(Num* n){
    return n->get_value();
}

int Interpreter::interpret(){
    ast = parser.parse();
    return ast->accept(this).integer; 
}

void Interpreter::display(){
	cout << interpret() << endl; 
}

/* Worked before the pascal-like features were added -- too tedious to maintain so I nixed it 
VisitorRPN::VisitorRPN(string text) : NodeVisitor(text) {}
	
void VisitorRPN::display(){
	ast = parser.parse(); 
	ast->accept(this); 
} 

Value VisitorRPN::visit(BinOp* n){
	n->left->accept(this);
	n->right->accept(this); 
	cout << n->get_value().op << " ";
	
	// TODO update, this is just here to satisfy the functon signature 
	Value val; 
	return val;  
}

Value VisitorRPN::visit(UnOp* n){
	cout << n->get_value().op;
	n->operand->accept(this);

	Value val; 
	return val; 
}

Value VisitorRPN::visit(Num* n){
	cout << n->get_value().integer << " "; 
	Value val; 
	return val; 
}

VisitorLisp::VisitorLisp(string text) : NodeVisitor(text) {} 

void VisitorLisp::display(){
	ast = parser.parse(); 
	ast->accept(this); 
} 

Value VisitorLisp::visit(BinOp* n){
	cout << '(' << n->get_value().op << " ";
	n->left->accept(this);
	cout << " "; 
	n->right->accept(this); 
	cout << ')'; 
	// TODO update, this is just here to satisfy the functon signature 
	Value val; 
	return val;  
}

Value VisitorLisp::visit(UnOp* n){
	cout << n->get_value().op;
	n->operand->accept(this);

	Value val; 
	return val; 
}

Value VisitorLisp::visit(Num* n){
	cout << n->get_value().integer;  
	Value val; 
	return val; 
}
*/ 
