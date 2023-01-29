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
    SensorDataFrame new_data = { 
        digitalRead(this->left_pin), 
        digitalRead(this->forward_pin), 
        digitalRead(this->right_pin)
    };

    return new_data;
}


void Sensor::cleanup() {
    pinMode(this->left_pin, INPUT);
    pinMode(this->forward_pin, INPUT);
    pinMode(this->right_pin, INPUT);
}