#include <iostream>
#include "queue.h"

using namespace std;
using namespace PQueue;

P_Queue::P_Queue() {
    qNode = NULL;
}

void P_Queue::enqueue(Queue_Node* node) {
    Queue_Node* t, * q;
    t = new Queue_Node;

    if (qNode == NULL || node->f < qNode->f) {
        t->next = qNode;
        apply(node, t);
        qNode = t;
    }
    else {
        q = qNode;
        while (q->next != NULL && q->next->f <= node->f) {
            q = q->next;
        }
        t->next = q->next;
        q->next = t;
        apply(node, t);
    }
}


bool P_Queue::find(int num) {
    Queue_Node* t;
    t = qNode;
    while (t->next != NULL && t->loc != num) {
        t = t->next;
    }
    if (t->loc == num) {
        return 1;
    }
    else {
        return 0;
    }
}


Queue_Node* P_Queue::findptr(int num) {
    Queue_Node* t;
    t = qNode;
    while (t->next != NULL && t->loc != num) {
        t = t->next;
    }
    if (t->loc == num) {
        return t;
    }
    else {
        t = NULL;
        return t;
    }
}


Queue_Node* P_Queue::dequeue(void) {
    Queue_Node* t;
    if (qNode == NULL) {
        return t;
    }
    else {
        t = qNode;
        qNode = qNode->next;
        return t;
    }
}


void P_Queue::apply(Queue_Node* input_node, Queue_Node* target_node) {
    target_node->f = input_node->f;
    target_node->g = input_node->g;
    target_node->h = input_node->h;
    target_node->loc = input_node->loc;
    target_node->parent = input_node->parent;
    target_node->ob = input_node->ob;
}
