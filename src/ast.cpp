#include "ast.hpp" 
#include "node_visitor.hpp" 
#include <ctype.h> 

using std::list; 

AST::AST(){

}

AST::AST(Token token){
    this->token = token; 
}

Value AST::get_value(){
    return token.get_value(); 
}

Type AST::get_type(){
    return token.get_type(); 
}

Token AST::get_token(){
    return token; 
}

Compound::Compound(list<AST*> children){
    this->children = children; 
}

Value Compound::accept(NodeVisitor* v){
    return v->visit(this);
}

void Compound::add_child(AST* child){
    children.push_back(child);
}

Variable::Variable(Token token) : AST(token){

}

Value Variable::accept(NodeVisitor* v){
    return v->visit(this);
}

const char* Variable::get_name(){
    return get_value().str; 
}

Assignment::Assignment(Variable* left, AST* right){
    this->left = left; 
    this->right = right; 
}

Value Assignment::accept(NodeVisitor* v){
    return v->visit(this); 
}

const char* Assignment::get_name(){
    return left->get_value().str; 
}
Value NoOp::accept(NodeVisitor* v){
    return v->visit(this); 
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
