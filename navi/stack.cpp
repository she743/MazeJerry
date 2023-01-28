#include <iostream>
#include "stack.h"

using namespace std;
using namespace PStack;


P_Stack::P_Stack() {
    top = NULL;
}


void P_Stack::push(Stack_Node* s_node) {
    Stack_Node* t, * q;
    t = new Stack_Node;
    q = new Stack_Node;

    if (top == NULL) {
        t->next = NULL;
        apply(s_node, t);
        top = t;
    }
    else{
        q->next = top;
        apply(s_node, q);
        top = q;
    }
}


void P_Stack::apply(Stack_Node* input_node, Stack_Node* target_node) {
    target_node->loc = input_node->loc;
    target_node->parent = input_node->parent;
}


Stack_Node* P_Stack::pop(void) {
    Stack_Node* t;
    t = new Stack_Node;

    if (top == NULL) {
        cout << "top is NULL" << endl;
        return top;
    }
    else {
        t = top;
        top = top->next;
        return t;
        free(t);
    }
}

