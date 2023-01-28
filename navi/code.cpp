#include "windows.h"
#include <iostream>
#include "queue.h"
#include<cmath>
#include<cstdlib>

int start = 110; 
int target = 502;

using namespace std;
/*
    Define main Priority Queue Node Structure.
    ---- 
 */
struct Queue_Node {
    int loc;
    int parent;
    int ob;
    int g;
    int h;
    int f;
    struct Queue_Node* next;
};


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
class P_Queue {
public:
    Queue_Node* qNode;
    P_Queue() {
        qNode = NULL;
    }

    void enqueue(Queue_Node* node) {
        // cout << node->f << endl;

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
        t = new Queue_Node;
        if (qNode == NULL) {
            return t;
        }
        else {
            t = qNode;
            qNode = qNode->next;
            return t;
        }
    }

    bool find(int num) {
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

    Queue_Node* findptr(int num) {
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

struct Stack_Node {
    int loc;
    int parent;
    struct Stack_Node* next;
};
class P_Stack {
public:
    Stack_Node* top;
    P_Stack() {
        top = NULL;
    }

    void push(Stack_Node* s_node){
        // cout << s_node->loc << endl;

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

    Stack_Node* pop() {
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

private:
    void apply(Stack_Node* input_node, Stack_Node* target_node) {
        target_node->loc = input_node->loc;
        target_node->parent = input_node->parent;
        }
};

void show(P_Queue* queue) {
    Queue_Node* ptr;
    ptr = queue->qNode;
    if (ptr == NULL) {
        cout << "Queue is Empty!!" << endl;
    }
    else {
        cout << "Queue is :";
        while (ptr != NULL) {
            cout << ptr->f << " -> ";
            ptr = ptr->next;
        }
        cout << "\n";
    }
}

int find_loc(int head, int s, int current) {
    int i = (head * 3 + s) % 4;
    int ask = 0;
    switch (i)
    {
    case 0:
        ask = current + 100;
        break;
    case 1:
        ask = current - 1;
        break;
    case 2:
        ask = current - 100;
        break;
    case 3:
        ask = current + 1;
        break;
    }
    return ask;
}

int cal_ob(int s, int sensor) {
    int obs;
    switch (s)
    {
    case 0:
        obs = sensor % 10;
        break;
    case 1:
        obs = (sensor % 100)/10;
        break;
    case 2:
        obs = sensor / 100;
        //cout << "ob : " << obs << endl;
        break;
    }
    obs = obs * 100;
    return obs;
}

struct movein {
    int motion;
    int new_head;
};

movein move_c(int head, int current, int expect) {
    int a = expect / 100 - current / 100;
    int b = expect % 100 - current % 100;
    int n = 0;

    //cout << a << endl;
    //cout << b << endl;

    movein result;
    result.motion = 0;
    result.new_head = 0;

    switch (a)
    {
    case 0:
        switch (b)
        {
        case -2:
            n = (head + 0) % 4;
            // cout << n << endl;
            break;
        case 2:
            n = (head + 2) % 4;
            //cout << n << endl;
            break;
        }
        break;
    case 2:
        n = (head + 3) % 4;
        //cout << n << endl;
        break;
    case -2:
        n = (head + 1) % 4;
        //cout << n << endl;
        break;
    }


    switch (n) 
    {
    case 0:
        result.motion = 0;
        result.new_head = head;
        //cout << result.motion << endl;
        //cout << result.new_head << endl;
        break;
    case 1:
        result.motion = 1;
        result.new_head = (head + 3) % 4;
        break;
    case 2:
        result.motion = 2;
        result.new_head = (head + 2) % 4;
        break;
    case 3:
        result.motion = 3;
        result.new_head = (head + 1) % 4;
        //cout << result.motion << endl;
        //cout << result.new_head << endl;
        break;
    }
    return result;
}

int main(void) {
    
    P_Queue closedlist;
    P_Queue openlist;
    Queue_Node node;
    P_Stack route;
    Stack_Node s_node;
    node.loc = start;
    node.parent = 0;
    node.ob = 0;
    node.g = 0;
    node.h = 0;
    node.f = 10000;

    s_node.loc = start;
    s_node.parent = 0;

    int g = 0;
    int h = 0;

    closedlist.enqueue(&node);
    openlist.enqueue(&node);
    route.push(&s_node);

    //show(&closedlist);
    int head = 0;
    int current = start;
    
    while (current != target) {
        int sensor;
        cout << current << endl;
        cout << "�������� �Է� (�� �� ��)";
        cin >> sensor;

        for (int s = 0; s < 3; s++) {
            int num = find_loc(head, s, current);
            if (!closedlist.find(num)) {
                if (cal_ob(s, sensor) == 0) {
                    int cc = cal_ob(s, sensor);
                    //cout << cc << endl;
                    num = find_loc(head, s, num);
                }
                Queue_Node n;
                n.loc = num;
                n.parent = current;
                n.ob = cal_ob(s, sensor); 
                n.g = g;
                float num_1 = pow(target / 100 - n.loc / 100, 2);
                float num_2 = pow(target % 100 - n.loc % 100, 2);
                float num_t = sqrt(num_1+num_2);
                n.h = num_t;
                n.f = n.g + n.h + n.ob;
                if (n.loc == target) {
                    n.f = 0;
                }

                if (openlist.find(num)) {
                    Queue_Node* ptr;
                    ptr = openlist.findptr(num);
                    if (ptr->f > n.f) {
                        ptr->f = n.f;
                        ptr->g = n.g;
                        ptr->h = n.h;
                        ptr->loc = n.loc;
                       // ptr->next = n.next;
                        ptr->ob = n.ob;
                        ptr->parent = n.parent;
                    }
               }
                else {
                    openlist.enqueue(&n);
                    cout << "n loc" << n.loc << endl;
                    cout << "n g" << n.g << endl;
                    cout << "n h" << n.h << endl;
                }
            }
        }
        //list�� node �߰�
        
        Queue_Node* expect = openlist.dequeue();
        closedlist.enqueue(expect);
        movein information;
        int motion_info;
        Stack_Node* back;
        if (expect->parent != current) {
            cout << expect->parent << endl;
            while (route.top->parent != expect->parent) {
                back = route.pop();
                information = move_c(head, current, back->parent);
                motion_info = information.motion;
                
                cout << "expect -> loc" <<expect->loc << endl;


                if (expect->loc == target) {
                    cout << "if"  << endl;
                    break;
                }

                head = information.new_head;
                current = back->parent;
                cout << "move : " << motion_info << endl;
                cout << "head : " << head << endl;
                cout << "loc : " << back->loc << endl;
                cout << "parent : " << back->parent << endl;
                //cout << "111111" << endl;
            }
            back = route.pop();
            information = move_c(head, current, back->parent);
            motion_info = information.motion;
            head = information.new_head;
            current = back->parent;
            cout << "move : " << motion_info << endl;
            cout << "head : " << head << endl;
            cout << "----back----" << endl;
        }
        information = move_c(head, current, expect->loc);
        motion_info = information.motion;
        head = information.new_head;
        current = expect->loc;
        cout <<"current : " << current << endl;
        cout << "move : " << motion_info << endl;
        cout << "head : " <<head << endl;
        cout << "----forward----" << endl;
        s_node.loc = expect->loc;
        s_node.parent = expect->parent;
        route.push(&s_node);

        g++;
    }


/*movein asdf = move_c(0, 110, 108);
cout << asdf.motion << endl;
cout << asdf.new_head << endl;*/
return 0;
}
