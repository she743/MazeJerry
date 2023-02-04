#include "queue.h"
#include "stack.h"
#include <cppgpio.hpp>
#include <iostream>
#include <cmath>
#include "wiringPi.h"
#include "sensing.h"
#include "motor.h"

// !! change start and target location !!
#define START 216
#define TARGET 1202
//x*100+y

using namespace MotorCTL;

// !!change pin number!!
// IR sensor for detecting wall
int irpin_l = 4;
int irpin_f = 5;
int irpin_r = 6;

// TCRT sensor for detecting line
int left_tcrt_pin = 2;
int middle_tcrt_pin = 3;
int right_tcrt_pin = 0;

// Motor pin
Motor motors (26, 1, 24, 23);


int ir_sensor_data = 0;

using namespace std;
using namespace PStack;
using namespace PQueue;

using namespace Sensing;


struct movein {
    int motion;
    int new_head;
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



Sensor tcrt(left_tcrt_pin, middle_tcrt_pin, right_tcrt_pin);
SensorDataFrame tcrt_data;
int tcrt_data_int =0;


void motion_forward( void ){
    tcrt_data = tcrt.get();
    tcrt_data_int = tcrt_data.data; // 1 is white
    while(tcrt_data_int != 101 || tcrt_data_int != 111){
        motors.forward();
        tcrt_data = tcrt.get();
        tcrt_data_int = tcrt_data.data;
        }

    while(tcrt_data_int != 010 || tcrt_data_int != 000){
        motors.forward();
        tcrt_data = tcrt.get();
        tcrt_data_int = tcrt_data.data;
        if(tcrt_data_int == 001 || tcrt_data_int == 011){
            motors.calibL();
        }
        else if(tcrt_data_int == 100 || tcrt_data_int == 110){
            motors.calibR();
        }
        }
    motors.stop();
    tcrt.cleanup();
    }
    /*
        while sensor data is not 010 or 000
            do:
                forward
                sensor data = sensor.get()

        forward() // to get away from the black line
        delay(100);

        while sensor data is not 101 or 111
            do: 
                forward
                sensor data = sensor.get()
        
        stop();
    */ 

void motion_turn_right( void ){
    tcrt_data = tcrt.get();
    tcrt_data_int = tcrt_data.data;
    while(tcrt_data_int != 101 || tcrt_data_int != 111){
        motors.turn_right();
        tcrt_data = tcrt.get();
        tcrt_data_int = tcrt_data.data;
        }

    motors.turn_right();
    delay(100);

    while(tcrt_data_int != 010 || tcrt_data_int != 000){
        motors.turn_right();
        tcrt_data = tcrt.get();
        tcrt_data_int = tcrt_data.data;
        }
    motors.stop();
    tcrt.cleanup();
    }

void motion_turn_left( void ){
    tcrt_data = tcrt.get();
    tcrt_data_int = tcrt_data.data;
    while(tcrt_data_int != 101 || tcrt_data_int != 111){
        motors.turn_left();
        tcrt_data = tcrt.get();
        tcrt_data_int = tcrt_data.data;
        }

    motors.turn_left();
    delay(100);

    while(tcrt_data_int != 010 || tcrt_data_int != 000){
        motors.turn_left();
        tcrt_data = tcrt.get();
        tcrt_data_int = tcrt_data.data;
        }
    motors.stop();
    tcrt.cleanup();
    }


void motion(int move_info){
    switch(move_info){
        case 0:
            // forward
            motion_forward();
            break;
        case 1:
            // left + forward
            motion_turn_left();
            motion_forward();
            break;
        case 2:
            // right + right + forward
            motion_turn_right();
            motion_turn_right();
            motion_forward();
            break;
        case 3:
            // right + forward
            motion_turn_right();
            motion_forward();
            break;
        default:
            //forward?
            motion_forward();
            break;
    }
}




int main(void) {
    while(1)
    {
        tcrt_data = tcrt.get();
        tcrt_data_int = tcrt_data.data; // 1 is white
        switch(tcrt_data_int){
            case 000 : motors.forward(); break;
            case 001 : motors.calibL(); break;
            case 010 : motors.stop(); break;
            case 011 : motors.calibL(); break;
            case 100 : motors.calibR(); break;
            case 101 : motors.forward(); break;
            case 110 : motors.calibR(); break;
            case 111 : motors.turn_left(); delay(1000); break;
            default : motors.stop();
        }
    }
    motors.stop();
    tcrt.cleanup();
    
    











    // P_Queue closedlist;
    // P_Queue openlist;
    // P_Stack route;
    // Stack_Node s_node;

    // Queue_Node node;
    // node.loc = START;
    // node.parent = 0;
    // node.ob = 0;
    // node.g = 0;
    // node.h = 0;
    // node.f = 10000;

    // s_node.loc = START;
    // s_node.parent = 0;

    // int g = 0;
    // int h = 0;

    // closedlist.enqueue(&node);
    // openlist.enqueue(&node);
    // route.push(&s_node);

    // //show(&closedlist);
    // int head = 1;
    // int current = START;
    
    // while (current != TARGET) {
    //     /*
    //     cout << current << endl;
    //     cout << "Enter sensor values (L, F, R):";
    //     cin >> sensor;
    //     */

    //     Sensor sensors(irpin_l,irpin_f,irpin_r);
    //     SensorDataFrame irdata = sensors.get();
    //     ir_sensor_data = irdata.l_data*100 + irdata.f_data*10 + irdata.r_data;
    //     sensors.cleanup();


    //     for (int s = 0; s < 3; s++) {
    //         int num = find_loc(head, s, current);
    //         if (!closedlist.find(num)) {
    //             if (cal_ob(s, ir_sensor_data) == 0) {
    //                 int cc = cal_ob(s, ir_sensor_data);
    //                 //cout << cc << endl;
    //                 num = find_loc(head, s, num);
    //             }
    //             Queue_Node n;
    //             n.loc = num;
    //             n.parent = current;
    //             n.ob = cal_ob(s, ir_sensor_data); 
    //             n.g = g;
    //             float num_1 = pow(TARGET / 100 - n.loc / 100, 2);
    //             float num_2 = pow(TARGET % 100 - n.loc % 100, 2);
    //             float num_t = sqrt(num_1+num_2);
    //             n.h = num_t;
    //             n.f = n.g + n.h + n.ob;
    //             if (n.loc == TARGET) {
    //                 n.f = 0;
    //             }

    //             if (openlist.find(num)) {
    //                 Queue_Node* ptr;
    //                 ptr = openlist.findptr(num);
    //                 if (ptr->f > n.f) {
    //                     ptr->f = n.f;
    //                     ptr->g = n.g;
    //                     ptr->h = n.h;
    //                     ptr->loc = n.loc;
    //                    // ptr->next = n.next;
    //                     ptr->ob = n.ob;
    //                     ptr->parent = n.parent;
    //                 }
    //            }
    //             else {
    //                 openlist.enqueue(&n);
    //                 cout << "n loc" << n.loc << endl;
    //                 cout << "n g" << n.g << endl;
    //                 cout << "n h" << n.h << endl;
    //             }
    //         }
    //     }
        
    //     Queue_Node* expect = openlist.dequeue();
    //     closedlist.enqueue(expect);
    //     movein information;
    //     int motion_info;
    //     Stack_Node* back;
    //     if (expect->parent != current) {
    //         cout << expect->parent << endl;
    //         while (route.top->parent != expect->parent) {
    //             back = route.pop();
    //             information = move_c(head, current, back->parent);
    //             motion_info = information.motion;
    //             cout << "expect -> loc" <<expect->loc << endl;


    //             if (expect->loc == TARGET) {
    //                 cout << "if"  << endl;
    //                 break;
    //             }

    //             head = information.new_head;
    //             current = back->parent;
    //             cout << "move : " << motion_info << endl;
    //             cout << "head : " << head << endl;
    //             cout << "loc : " << back->loc << endl;
    //             cout << "parent : " << back->parent << endl;
    //             motion(motion_info);
    //             //cout << "111111" << endl;
    //         }
    //         back = route.pop();
    //         information = move_c(head, current, back->parent);
    //         motion_info = information.motion;
    //         head = information.new_head;
    //         current = back->parent;
    //         cout << "move : " << motion_info << endl;
    //         cout << "head : " << head << endl;
    //         cout << "----back----" << endl;
    //         motion(motion_info);
    //     }
    //     information = move_c(head, current, expect->loc);
    //     motion_info = information.motion;
    //     head = information.new_head;
    //     current = expect->loc;
    //     cout <<"current : " << current << endl;
    //     cout << "move : " << motion_info << endl;
    //     cout << "head : " <<head << endl;
    //     cout << "----forward----" << endl;
    //     motion(motion_info);
    //     s_node.loc = expect->loc;
    //     s_node.parent = expect->parent;
    //     route.push(&s_node);

    //     g++;
    // }


/*movein asdf = move_c(0, 110, 108);
cout << asdf.motion << endl;
cout << asdf.new_head << endl;*/
return 0;
}
