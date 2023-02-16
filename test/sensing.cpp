#include "sensing.h"
#include <wiringPi.h>

using namespace Sensing;


Sensor::Sensor(int pin0, int pin1, int pin2) {
    /*
        Sensor Instance Initialize!
    */
    wiringPiSetup();

    this->left_pin = pin0;
    this->forward_pin = pin1;
    this->right_pin = pin2;

    pinMode(this->left_pin, INPUT);
    pinMode(this->forward_pin, INPUT);
    pinMode(this->right_pin, INPUT);
}


SensorDataFrame Sensor::get() {
    /*
        Read Sensor's values (Use 'digitalRead()' function).
    */
    int l_data = digitalRead(this->left_pin);
    int f_data = digitalRead(this->forward_pin);
    int r_data = digitalRead(this->right_pin);
    int data = l_data * 100 + f_data * 10 + r_data;

    SensorDataFrame new_data = { l_data, f_data, r_data, data };
    return new_data;
}


void Sensor::cleanup() {
    pinMode(this->left_pin, INPUT);
    pinMode(this->forward_pin, INPUT);
    pinMode(this->right_pin, INPUT);
}