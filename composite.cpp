#include "composite.h"

//--------------------------------------------------------------------------
// Op Class
//--------------------------------------------------------------------------
Op::Op() : Base(), value(0){};
Op::Op(double val) : Base(), value(val){};

Base* Op::get_left() { return NULL; }
Base* Op::get_right() { return NULL; }
void Op::print() { cout << this->value; }
double Op::evaluate() { return this->value; };
Iterator* Op::create_iterator() { return new NullIterator(this); }

//--------------------------------------------------------------------------
// Operator Base Class
//--------------------------------------------------------------------------
Operator::Operator() : Base(){ };
Operator::Operator(Base* l, Base* r) : left(l), right(r){  };

Base* Operator::get_left() { return left; };
Base* Operator::get_right() { return right; };
Iterator* Operator::create_iterator() { return new OperatorIterator(this); }

//--------------------------------------------------------------------------
// Unary Base Class
//--------------------------------------------------------------------------
UnaryOperator::UnaryOperator() : Base(){};
UnaryOperator::UnaryOperator(Base* c) : child(c) { };

Base* UnaryOperator::get_left() { return child; }
Base* UnaryOperator::get_right() { return NULL; }
Iterator* UnaryOperator::create_iterator() { return new UnaryIterator(this); }

//--------------------------------------------------------------------------
// Add Class
//--------------------------------------------------------------------------
Add::Add() : Operator() { };
Add::Add(Base* left, Base* right) : Operator(left,right) { };

void Add::print() { cout << "+"; }
double Add::evaluate() { return this->left->evaluate() + this->right->evaluate(); };

//--------------------------------------------------------------------------
// Sub Class
//--------------------------------------------------------------------------
Sub::Sub() : Operator() { };
Sub::Sub(Base* left, Base* right) : Operator(left,right) { };

void Sub::print() { cout << "-"; }
double Sub::evaluate() { return this->left->evaluate() - this->right->evaluate(); };

//--------------------------------------------------------------------------
// Mult Class
//--------------------------------------------------------------------------
Mult::Mult() : Operator() { };
Mult::Mult(Base* left, Base* right) : Operator(left,right) { };

void Mult::print() { cout << "*"; }
double Mult::evaluate() { return this->left->evaluate() * this->right->evaluate(); };

//--------------------------------------------------------------------------
// Sqr Class
//--------------------------------------------------------------------------
Sqr::Sqr() : UnaryOperator() { };
Sqr::Sqr(Base* child) : UnaryOperator(child) { };

void Sqr::print() { cout << "^2"; }
double Sqr::evaluate() { return pow(this->child->evaluate(),2); };

//--------------------------------------------------------------------------
// Root Class
//--------------------------------------------------------------------------
Root::Root() : UnaryOperator() { };
Root::Root(Base* child) : UnaryOperator(child) { };

void Root::print() { cout << "ROOT"; }
double Root::evaluate() { return this->child->evaluate(); };



//Here comes everything else
PreOrderIterator::PreOrderIterator() {

}

PreOrderIterator::PreOrderIterator(Base* ptr) {
	self_ptr = ptr;
}


void PreOrderIterator::first() {
	//Iterator<Base*>* iter = this->self_ptr->create_iterator();
	Iterator* iter = this->self_ptr->create_iterator();
	if (iter) {
		iter->first();
		while (!iterators.empty()) { //remove all from the stack
			this->iterators.pop();
		}
		this->iterators.push(iter);
	}
}

void PreOrderIterator::next() {
	//Iterator<Base*>* iter = this->iterators.top()->current()->create_iterator();
	Iterator* iter = this->iterators.top()->current()->create_iterator();
	iter->first();
	this->iterators.push(iter);
	while (this->iterators.size() > 0 && this->iterators.top()->is_done()) {
		delete this->iterators.top();
		iterators.pop();
		if(!iterators.empty()) {
			this->iterators.top()->next();
		}
	}
}

bool PreOrderIterator::is_done() {
	if (iterators.empty()) 
		return true;
	else
		return false;
}

Base* PreOrderIterator::current() {
	if (this->iterators.size() > 0) {
		return this->iterators.top()->current();
	}
	else {
		return NULL;
	}
}
