#include "ast.hpp" 
#include "node_visitor.hpp" 
Value AST::get_value(){
    return token.get_value(); 
}

Type AST::get_type(){
    return token.get_type(); 
}

Token AST::get_token(){
    return token; 
}

BinOp::BinOp(){
    left = nullptr;
    token = Token(); 
    right = nullptr;  
}

BinOp::BinOp(AST* left, Token op, AST* right){
    this->left = left; 
    token = op; 
    this->right = right; 
}

Value BinOp::accept(NodeVisitor* v){
    return v->visit(this); 
}

UnOp::UnOp(Token op, AST* operand){
	token = op;
	this->operand = operand; 	
}

Value UnOp::accept(NodeVisitor* v){
	return v->visit(this); 
}

Num::Num(){
    token = Token(); 
}

Num::Num(Token token){
    this->token = token; 
}

Value Num::accept(NodeVisitor* v){
    return v->visit(this); 
}
