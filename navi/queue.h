#include "windows.h"
#include <iostream>

namespace PQueue {
struct Queue_Node {
    int loc;
    int parent;
    int ob;
    int g;
    int h;
    int f;
    struct Queue_Node* next;
};

class P_Queue {
    /*
        Define Priority Queue class
        ---
            Public funcs:
                - enqueue:
                    Return Type: void
                    Parameters: Queue_Node
                    Info:
                        Insert node(Queue_Node type) into Priority Queue.
                        And then, sorting all elements.

                - dequeue:
                    Return Type: Queue_Node
                    Parameters: void
                    Info:
                        Return node(Queue_Node type)

            Private funcs:
                - sorting:
                    Return Type: void
                    Parameters: void
    */
public:
    Queue_Node* qNode;
    P_Queue() {
        qNode = NULL;
    }

    void enqueue(Queue_Node* node) {
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

    Queue_Node* dequeue(void) {
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

private:
    void apply(Queue_Node* input_node, Queue_Node* target_node) {
        target_node->f = input_node->f;
        target_node->g = input_node->g;
        target_node->h = input_node->h;
        target_node->loc = input_node->loc;
        target_node->parent = input_node->parent;
        target_node->ob = input_node->ob;
    }
};
}