#include "queue.h"
#include "stack.h"
#include <cppgpio.hpp>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include "wiringPi.h"
#include "sensing.h"
#include "motor.h"
#include "softPwm.h"

// !! change start and target location !!
#define START 216
#define TARGET 1202
#define IR_LEFT_PIN 27
#define IR_FOWRARD_PIN 29
#define IR_RIGHT_PIN 28
#define TRCT_LEFT_PIN 6
#define TRCT_CENTER_PIN 5
#define TRCT_RIGHT_PIN 4
#define MOTOR_RIGHT_FORMARD 26
#define MOTOR_RIGHT_BACKMARD 1
#define MOTOR_LEFT_FORMARD 24
#define MOTOR_LEFT_BACKMARD 23
#define PIN_A 3 // Encoder pin A left(3,0)
#define PIN_B 0 // Encoder pin B
#define PIN_C 2 // Encoder pin C right(2,7)
#define PIN_D 7 // Encoder pin D

using namespace MotorCTL;
using namespace std;
using namespace PStack;
using namespace PQueue;
using namespace Sensing;


int counterL = 0; // Encoder counter
int counterR = 0;
int prev_A = 0; // Previous state of pin A
int prev_C = 0;


struct movein {
    int motion;
    int new_head;
};


void lineStatus(int data) {
    if(data==000) cout << "lll" << endl;
    else if(data==001) cout << "ll-" << endl;
    else if(data==010) cout << "l-l" << endl;
    else if(data==011) cout << "l--" << endl;
    else if(data==100) cout << "-ll" << endl;
    else if(data==101) cout << "-l-" << endl;
    else if(data==110) cout << "--l" << endl;
    else if(data==111) cout << "---" << endl;
}

void wallStatus(int data) {
    if(data==000) cout << "   " << endl;
    else if(data==001) cout << "  l" << endl;
    else if(data==010) cout << " ' " << endl;
    else if(data==011) cout << " 'l" << endl;
    else if(data==100) cout << "l  " << endl;
    else if(data==101) cout << "l l" << endl;
    else if(data==110) cout << "l' " << endl;
    else if(data==111) cout << "l'l" << endl;
}


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

    //motion forward: if tcrt data 101 or 111
    //motion turn_left : if tcrt data 100 or 110
    //motion turn_right : if tcrt data 001 or 011
    //else motion default forward
    

void interrupt_handler_left(void) {
    int curr_A = digitalRead(PIN_A);
    int curr_B = digitalRead(PIN_B);

    if (curr_A != prev_A) {
        if(curr_B != curr_A) counterL++;
        else counterL--;
    }
    prev_A = curr_A;
}

void interrupt_handler_right(void) {
    int curr_C = digitalRead(PIN_C);
    int curr_D = digitalRead(PIN_D);

    if (curr_C != prev_C) {
        if(curr_D != curr_C) counterR++;
        else counterR--;
    }
    prev_C = curr_C;
}

int encoderLeft() {
	wiringPiSetup();

    softPwmCreate( PIN_A, 0, 100 );
    softPwmCreate( PIN_B, 0, 100 );
        
    wiringPiSetup();
        
    pinMode(PIN_A, INPUT);
    pinMode(PIN_B, INPUT);

    if (wiringPiSetup() == -1) {
        return 1;
    }

    wiringPiISR(PIN_A, INT_EDGE_BOTH, &interrupt_handler_left);

    while (counterL<740) {
        // cout << "Counter value: " << counterL << endl;
		// delay(10);
    }
	counterL = 0;
    prev_A = 0;
	return 0;
}

int encoderRight() {
	wiringPiSetup();

    softPwmCreate( PIN_C, 0, 100 );
    softPwmCreate( PIN_D, 0, 100 );
        
    wiringPiSetup();
        
    pinMode(PIN_C, INPUT);
    pinMode(PIN_D, INPUT);

    if (wiringPiSetup() == -1) {
        return 1;
    }

    wiringPiISR(PIN_C, INT_EDGE_BOTH, &interrupt_handler_right);

    while (counterR<850) {
        // cout << "Counter value: " << counterR << endl;
		// delay(10);
    }
	counterR = 0;
    prev_C = 0;
	return 0;
}

int encoder() {
	wiringPiSetup();

    softPwmCreate( PIN_A, 0, 100 );
    softPwmCreate( PIN_B, 0, 100 );
    softPwmCreate( PIN_C, 0, 100 );
    softPwmCreate( PIN_D, 0, 100 );
        
    wiringPiSetup();

    pinMode(PIN_A, INPUT);
    pinMode(PIN_B, INPUT);  
    pinMode(PIN_C, INPUT);
    pinMode(PIN_D, INPUT);

    if (wiringPiSetup() == -1) {
        return 1;
    }

    wiringPiISR(PIN_A, INT_EDGE_BOTH, &interrupt_handler_left);
    wiringPiISR(PIN_C, INT_EDGE_BOTH, &interrupt_handler_right);

    while (abs(counterR - counterL) < 1600) {
        // cout << "Counter value: " << counterL << endl;
		// delay(10);
    }
    counterL = 0;
	counterR = 0;
    prev_A = 0;
    prev_C = 0;
	return 0;
}

void motion_forward( Sensor tcrt, Motor motors ){
    SensorDataFrame tcrt_data = tcrt.get();
    int tcrt_data_int = tcrt_data.data;
    motors.forward();
    delay(1000);
    motors.stop();

    cout << "out" << endl;
	delay(200);
	tcrt_data = tcrt.get();
    tcrt_data_int = tcrt_data.data;
    cout << tcrt_data_int << endl;
    while(tcrt_data_int != 000){
        if(tcrt_data_int == 101) motors.forward();
        else if(tcrt_data_int == 011 || tcrt_data_int == 001) motors.calibL();
        else if(tcrt_data_int == 110 || tcrt_data_int == 100) motors.calibR();
		else motors.forward();

		tcrt_data = tcrt.get();
        tcrt_data_int = tcrt_data.data;
        lineStatus(tcrt_data_int);
    }
    motors.stop();
    delay(700);
    tcrt.cleanup();
}

void motion_turn_right( Sensor tcrt, Motor motors ){
	motors.turn_right();
	encoder();
	motors.stop();
	delay(700);
    tcrt.cleanup();
    }

void motion_turn_left( Sensor tcrt, Motor motors ){
	motors.turn_left();
	encoder();
	motors.stop();
	delay(700);
    tcrt.cleanup();
    }

void motion(int move_info,  Sensor tcrt, Motor motors ){
    // cout << "motion 1: " << tcrt.get().data << endl;
    switch(move_info){
        case 0:
            // forward
            // cout << "F" << tcrt.get().data << endl;
            motion_forward( tcrt, motors );
            break;
        case 1:
            // left + forward
            // cout << "LF" << tcrt.get().data << endl;
            motion_turn_left( tcrt, motors );
            motion_forward( tcrt, motors );
            break;
        case 2:
            // right + right + forward
            // cout << "RRF" << tcrt.get().data << endl;
            motion_turn_right( tcrt, motors );
            motion_turn_right( tcrt, motors );
            motion_forward( tcrt, motors );
            break;
        case 3:
            // right + forward
            // cout << "RF" << tcrt.get().data << endl;
            motion_turn_right( tcrt, motors );
            motion_forward( tcrt, motors );
            break;
        default:
            //forward?
            cout << "F?" << tcrt.get().data << endl;
            motion_forward( tcrt, motors );
            break;
    }
}





int main(void) {
	
    //int any_key;
    //cin >> any_key;

    // Motor pin
    Motor motors(MOTOR_RIGHT_FORMARD, MOTOR_RIGHT_BACKMARD, MOTOR_LEFT_FORMARD, MOTOR_LEFT_BACKMARD);
    Sensor tcrt(TRCT_LEFT_PIN, TRCT_CENTER_PIN, TRCT_RIGHT_PIN);
    Sensor ir_sensors( IR_LEFT_PIN, IR_FOWRARD_PIN, IR_RIGHT_PIN );

    // motion(0, tcrt, motors);
	
	P_Queue closedlist;
    P_Queue openlist;
    P_Stack route;
    Stack_Node s_node;
    P_Queue neighbor;

    Queue_Node node;
    node.loc = START;
    node.parent = 0;
    node.ob = 0;
    node.g = 0;
    node.h = 0;
    node.f = 10000;

    s_node.loc = START;
    s_node.parent = 0;

    int g = 0;
    int h = 0;

    closedlist.enqueue(&node);
    openlist.enqueue(&node);
    route.push(&s_node);
    

    //show(&closedlist);
    int head = 1;
    int current = START;
    
    movein information;
    int motion_info;

    while (current != TARGET) {

        cout << current << endl;
        /* 
        cout << "neighbor empty? " << neighbor.is_empty() << endl;
        cout << "Enter sensor values (L, F, R):";
        cin.clear();
        cin >> ir_sensor_data;
        cout << ir_sensor_data << endl;
        */

        
        SensorDataFrame irdata = ir_sensors.get();
        int ir_sensor_data = irdata.data;

        cout << ir_sensor_data << endl;
        


        if(ir_sensor_data == 111){
            // find minimum value in open list
            cout << "ir_senosr_data is 111" << endl;
            Queue_Node* expect = openlist.dequeue();
            closedlist.enqueue(expect);
            Stack_Node* back;
            
            cout << "expect : " << expect->loc << endl;

            while (route.top->parent != expect->parent) {
                back = route.pop();
                information = move_c(head, current, back->parent);
                motion_info = information.motion;
                cout << "expect -> loc" <<expect->loc << endl;


                if (expect->loc == TARGET) {
                    cout << "if"  << endl;
                    break;
                }

                head = information.new_head;
                current = back->parent;
                motion(motion_info, tcrt, motors);
                cout << "move : " << motion_info << endl;
                cout << "head : " << head << endl;
                cout << "loc : " << back->loc << endl;
                cout << "parent : " << back->parent << endl;

                /////new one check!!
                //Queue_Node* return_node = closedlist.node_delete(back->loc);
                //openlist.enqueue(return_node);

                //motion(motion_info, tcrt, motors);
                g--;
                //cout << "111111" << endl;
            }

            back = route.pop();
            information = move_c(head, current, back->parent);
            motion_info = information.motion;
            head = information.new_head;
            current = back->parent;
            cout << "move : " << motion_info << endl;
            motion(motion_info, tcrt, motors);
            
            cout << "head : " << head << endl;
            cout << "----back----" << endl;
            //motion(motion_info, tcrt, motors);

            /////new one check!!
                //Queue_Node* return_node = closedlist.node_delete(back->loc);
                //openlist.enqueue(return_node);
                
            g--;

            information = move_c(head, current, expect->loc);
            motion_info = information.motion;
            head = information.new_head;
            current = expect->loc;
            cout << "move : " << motion_info << endl;
            motion(motion_info, tcrt, motors);
            cout <<"current : " << current << endl;
            
            cout << "head : " <<head << endl;
            cout << "----forward----" << endl;
            //motion(motion_info, tcrt, motors);
            s_node.loc = expect->loc;
            s_node.parent = expect->parent;
            route.push(&s_node);

            g++;

        }
        else{
            // calculate node information and move   
            for (int s = 0; s < 3; s++) {
                /*
                    Searching enable path.
                */
                int num = find_loc(head, s, current);
                cout << "num : " << num << endl;
                if (!closedlist.find(num)) {
                    if (cal_ob(s, ir_sensor_data) == 0) {
                        int cc = cal_ob(s, ir_sensor_data);
                        //cout << cc << endl;
                        num = find_loc(head, s, num);
                    }
                    Queue_Node n;
                    n.loc = num;
                    n.parent = current;
                    n.ob = cal_ob(s, ir_sensor_data); 
                    n.g = g;
                    float num_1 = pow(TARGET / 100 - n.loc / 100, 2);
                    float num_2 = pow(TARGET % 100 - n.loc % 100, 2);
                    float num_3 = sqrt(num_1+num_2);
                    n.h = num_3;
                    n.f = n.g + n.h + n.ob;
                    if (n.loc == TARGET) {
                        n.f = 0;
                    }
                    neighbor.enqueue(&n);                
                }
            }
                Queue_Node* neighbor_node = neighbor.dequeue();
                closedlist.enqueue(neighbor_node);
                information = move_c(head, current, neighbor_node->loc);
                motion_info = information.motion;
                head = information.new_head;
                current = neighbor_node->loc;
                cout << "move : " << motion_info << endl;
                motion(motion_info, tcrt, motors);
                cout <<"current : " << current << endl;
                
                cout << "head : " <<head << endl;
                cout << "----forward----" << endl;
                cout << "here?" << endl;
                //motion(motion_info, tcrt, motors);
                s_node.loc = neighbor_node->loc;
                s_node.parent = neighbor_node->parent;
                route.push(&s_node);

                g++;

                // compare 3 node and we have to find where we go
                while(neighbor.is_empty()){
                    neighbor_node = neighbor.dequeue();
                    int loc_of_node = neighbor_node->loc;
                    cout << "neighbor is not empty" << endl;
                    if (openlist.find(loc_of_node)) {
                        Queue_Node* ptr;
                        ptr = openlist.findptr(loc_of_node);
                        cout << "----&&&&&----" <<endl;
                        if (ptr->f > neighbor_node->f) {
                            ptr->f = neighbor_node->f;
                            ptr->g = neighbor_node->g;
                            ptr->h = neighbor_node->h;
                            ptr->loc = neighbor_node->loc;
                            // ptr->next = n.next;
                            ptr->ob = neighbor_node->ob;
                            ptr->parent = neighbor_node->parent;
                        }
                    }
                    else {
                        openlist.enqueue(neighbor_node);
                        cout << "asdfghj" << endl;
                        // cout << "n loc" << n.loc << endl;
                        // cout << "n g" << n.g << endl;
                        // cout << "n h" << n.h << endl;
                    }
                }   
            

        }
        
        //cout << ir_sensors.get().data << endl;
        
        
        // if (expect->parent != current) {
        //     cout << expect->parent << endl;

        //     queue<int> q;
        //     int parent_val = 0;
        //     int location_to_find = current;

        //     while(parent_val != expect->parent){
        //         parent_val = closedlist.find_parent(location_to_find);
        //         q.push(parent_val);
        //         location_to_find = parent_val;
        //         cout << "push" << endl;
        //     }       

        //     int loc_to_go=0;
        //     while(!q.empty()){
        //         //move
        //         information = move_c(head, current, q.front());
        //         motion_info = information.motion;
        //         cout << "expect -> loc" <<expect->loc << endl;
                
        //         if (expect->loc == TARGET) {
        //             cout << "if"  << endl;
        //             break;
        //         }

        //         head = information.new_head;
        //         current = q.front();
        //         cout << "move : " << motion_info << endl;
        //         cout << "head : " << head << endl;
        //         cout << "loc : " << q.front() << endl;
        //         q.pop();
        //         cout << "pop" << endl;
        //     }
        
        }
    
    

        /*movein asdf = move_c(0, 110, 108);
        cout << asdf.motion << endl;
        cout << asdf.new_head << endl;*/
        motors.cleanup();
        tcrt.cleanup();
        ir_sensors.cleanup();
        return 0;
    
}
