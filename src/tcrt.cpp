#include "tcrt.h"
#include <wiringPi.h>

using namespace Tcrt;


Line_Sensor::Line_Sensor(int pin0, int pin1, int pin2) {
    /*
        Sensor Instance Initialize!
    */
    wiringPiSetup();

    this->l_pin = pin0;
    this->m_pin = pin1;
    this->r_pin = pin2;

    pinMode(this->l_pin, INPUT);
    pinMode(this->m_pin, INPUT);
    pinMode(this->r_pin, INPUT);
}

LineDataFrame Line_Sensor::get() {
    /*
        Read Sensor's values.
    */
    LineDataFrame read_data;
    read_data.left_d = digitalRead(this->l_pin);
    read_data.middle_d = digitalRead(this->m_pin);
    read_data.right_d = digitalRead(this->r_pin);

    return read_data;
}


void Line_Sensor::cleanup(){
    pinMode(this->l_pin, INPUT);
    pinMode(this->m_pin, INPUT);
    pinMode(this->r_pin, INPUT);
}