#include <iostream>
#include "motor.h"
#include "wiringPi.h"
#include "softPwm.h"

using namespace std;
using namespace MotorCTL;

int speed = 20;

Motor::Motor( int r_fpin, int r_bpin, int l_fpin, int l_bpin ) {
    wiringPiSetup();

    this->r_forward_pin = r_fpin;
    this->r_backward_pin = r_bpin;
    this->l_forward_pin = l_fpin;
    this->l_backward_pin = l_bpin;

    softPwmCreate( this->r_forward_pin, 0, 100 );
    softPwmCreate( this->r_backward_pin, 0, 100 );
    softPwmCreate( this->l_forward_pin, 0, 100 );
    softPwmCreate( this->l_backward_pin, 0, 100 );
}


void Motor::cleanup( void ) {
    pinMode( this->r_forward_pin, INPUT );
    pinMode( this->r_backward_pin, INPUT );
    pinMode( this->l_forward_pin, INPUT );
    pinMode( this->l_backward_pin, INPUT );
}



void Motor::forward( void ) {
    cout << "FORWARD " << endl;
    softPwmWrite(this->r_forward_pin, 0);
    softPwmWrite(this->r_backward_pin, speed);
    softPwmWrite(this->l_forward_pin, speed);
    softPwmWrite(this->l_backward_pin, 0);
}


void Motor::stop( void ) {
    // TURN 180 degrees
    cout << "STOP " << endl;
    softPwmWrite(this->r_forward_pin, 0);
    softPwmWrite(this->r_backward_pin, 0);
    softPwmWrite(this->l_forward_pin, 0);
    softPwmWrite(this->l_backward_pin, 0);
}


void Motor::turn_left( void ) {
    // MOVE LEFT
    cout << "LEFT" << endl;
    softPwmWrite(this->r_forward_pin, 0);
    softPwmWrite(this->r_backward_pin, speed);
    softPwmWrite(this->l_forward_pin, 0);
    softPwmWrite(this->l_backward_pin, speed);  
}


void Motor::turn_right( void ) {
    // MOVE RIGHT
    cout << "RIGHT" << endl;
    softPwmWrite(this->r_forward_pin, speed);
    softPwmWrite(this->r_backward_pin, 0);
    softPwmWrite(this->l_forward_pin, speed);
    softPwmWrite(this->l_backward_pin, 0);  
}

void Motor::calibR( void ) {
    // Calibrate movement
    cout << "Calibrating to R" << endl;
    softPwmWrite(this->r_forward_pin, 0);
    softPwmWrite(this->r_backward_pin, speed-10);
    softPwmWrite(this->l_forward_pin, speed);
    softPwmWrite(this->l_backward_pin, 0);  
}

void Motor::calibL( void ) {
    // Calibrate movement
    cout << "Calibrating to L" << endl;
    softPwmWrite(this->r_forward_pin, 0);
    softPwmWrite(this->r_backward_pin, speed);
    softPwmWrite(this->l_forward_pin, speed-10);
    softPwmWrite(this->l_backward_pin, 0);  
}