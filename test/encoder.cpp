#include <cppgpio.hpp>
#include <iostream>
#include <stdio.h>

#include "wiringPi.h"
#include "softPwm.h"

#define PIN_A 2 // Encoder pin A left(3,0)   right(2,7)
#define PIN_B 7 // Encoder pin B

using namespace std;

int counter = 0; // Encoder counter
int prev_A = 0; // Previous state of pin A

void interrupt_handler(void) {
    int curr_A = digitalRead(PIN_A);
    int curr_B = digitalRead(PIN_B);

    if (curr_A != prev_A) {
        if (curr_B != curr_A) {
            counter++;
        } else {
            counter--;
        }
    }

    prev_A = curr_A;
}

int main() {

    wiringPiSetup();

    softPwmCreate( PIN_A, 0, 100 );
    softPwmCreate( PIN_B, 0, 100 );
        
    wiringPiSetup();
        
    pinMode(PIN_A, INPUT);
    pinMode(PIN_B, INPUT);

    if (wiringPiSetup() == -1) {
        return 1;
    }

    wiringPiISR(PIN_A, INT_EDGE_BOTH, &interrupt_handler);

    while (true) {
        cout << "Counter value: " << counter << endl;
    }

    return 0;
}
