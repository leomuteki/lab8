#ifndef __COMPOSITE_CLASS__
#define __COMPOSITE_CLASS__

#include <iostream>
#include <sstream>
#include <math.h>
#include <string>
#include <cstdlib>
#include <stack>


using namespace std;

class Iterator;
class NullIterator;
class UnaryIterator;

//Abstract Base Class
class Base {
    public:
        Base(){};

        //virtual
        virtual void print() = 0;
        virtual double evaluate() = 0;
        virtual Iterator* create_iterator() = 0;
        virtual Base* get_left() = 0;
        virtual Base* get_right() = 0;
};
//Leaf Class
class Op: public Base {
    public:
        double value;
        Op();
        Op(double val);

        Base* get_left();
        Base* get_right();
        double evaluate(); 
        void print();
        Iterator* create_iterator();
        // void accept(Visitor* vis) {
        //     vis->opNode(this);
        // }
};

//Composite Base Classes
class Operator: public Base {
    protected:
        Base* left, *right;
    public:
        Operator();
        Operator(Base* l, Base* r);

        Base* get_left();
        Base* get_right();
        virtual double evaluate() = 0;	//Note: this is implicit in the inheritance, but can also be made explicit
        Iterator* create_iterator();
        // virtual void accept(Visitor* vis) = 0;
};

class UnaryOperator: public Base {
    protected:
        Base* child;
    public:
        UnaryOperator();
        UnaryOperator(Base* c);

        Base* get_left();
        Base* get_right();
        virtual double evaluate() = 0;	//Note: this is implicit in the inheritance, but can also be made explicit
        Iterator* create_iterator();
        // virtual void accept(Visitor* vis) = 0;
};

//Composite Classes
class Add: public Operator {
    public:
        Add();
        Add(Base* left, Base* right);

        void print();
        double evaluate();
        // void accept(Visitor* vis) {
        //     vis->addNode();
        // }
};

class Sub: public Operator {
    public:
        Sub();
        Sub(Base* left, Base* right);

        void print();
        double evaluate();
        // void accept(Visitor* vis) {
        //     vis->subNode();
        // }
};

class Mult: public Operator {
    public:
        Mult();
        Mult(Base* left, Base* right);

        void print();
        double evaluate();
        // void accept(Visitor* vis) {
        //     vis->multNode();
        // }
};

class Sqr: public UnaryOperator {
    public:
        Sqr();
        Sqr(Base* child);

        void print();
        double evaluate();
        // void accept(Visitor* vis) {
        //     vis->sqrNode();
        // }        
};

class Root: public UnaryOperator {
    public:
        Root();
        Root(Base* root);

        void print();
        double evaluate();
        // void accept(Visitor* vis) {
        //     vis->rootNode();
        // }
};

class Iterator {
protected:
    Base* self_ptr;
    Base* current_ptr;
public:
    Iterator() { }
    Iterator(Base* ptr) {
        this->self_ptr = ptr;
    }

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool is_done() = 0;
    virtual Base* current() = 0;
};

class OperatorIterator : public Iterator {
public:
    OperatorIterator(Base* ptr) {
        self_ptr = ptr;
    }

    void first() { 
        current_ptr = self_ptr->get_left(); 
        return;
    }
    void next() {
        if(is_done()) {
            return;
        }
        if(current_ptr == self_ptr->get_left()) {
            current_ptr = self_ptr->get_right();
        }
        else {
            current_ptr = NULL;
        }
        return;
    }
    bool is_done() {
        if(current_ptr == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
    Base* current() {
        return current_ptr;
    }
};

class UnaryIterator : public Iterator {
public:
    UnaryIterator(Base* ptr) {
        self_ptr = ptr;
    }

    void first() {
        current_ptr = self_ptr->get_left();
    }
    void next() {
        if(is_done()) {
            return;
        }
        else {
            current_ptr = NULL;
        }
    }
    bool is_done() {
        if(current_ptr != NULL) {
            return false;
        }
        else {
            return true;
        }
    }
    Base* current() {
        return current_ptr;
    }
};

class NullIterator : public Iterator {
public:
    NullIterator(Base* ptr) {
        self_ptr = NULL;
    }

    void first() { return; };
    void next() { return; };
    bool is_done() { return true; };
    Base* current() { return NULL; };
};

class PreOrderIterator : public Iterator {
protected:
    stack<Iterator*> iterators;

public:
    PreOrderIterator();
    PreOrderIterator(Base* ptr);

    void first();
    void next();
    bool is_done();
    Base* current();
};

class Visitor {
private:
    string output;
public:
    virtual void rootNode() = 0;
    virtual void sqrNode() = 0;
    virtual void multNode() = 0;
    virtual void subNode() = 0;
    virtual void addNode() = 0;
    virtual void opNode(Op* op) = 0;

    virtual void execute() = 0;

};

class PrintVisitor: public Visitor {
public:
    string output;
    PrintVisitor() {
        output = "";
    }
    void rootNode() {
        return;
    }
    void sqrNode() {
        output += " ^2";
    }
    void multNode() {
        output += " *";
    }
    void subNode() {
        output += " -";
    }
    void addNode() {
        output += " +";
    }
    void opNode(Op* op) {
        output += " ";
        output = op->value;
    }

    void execute() {
        cout << "Output: " << this->output << endl;
    }

};

#endif //__COMPOSITE_CLASS__
