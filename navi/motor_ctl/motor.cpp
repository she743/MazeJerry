#include <iostream>
#include "motor.h"
#include "wiringPi.h"
#include "softPwm.h"

using namespace std;
using namespace MotorCTL;


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


void Motor::move( Instruct instruction ) {
    if (instruction.dir) {
        // FORWARD or BACKWARD
        if (instruction.speed > 0) this->forward( instruction.speed );
        else this->backward();
    }
    else {
        // LEFT or RIGHT
        if (instruction.speed > 0) this->turn_left();
        else this->turn_right();
    }
    delay(5000);
}


void Motor::forward( int speed ) {
    cout << "FORWARD (" << speed << ")" << endl;
    softPwmWrite(this->r_forward_pin, 0);
    softPwmWrite(this->r_backward_pin, speed);
    softPwmWrite(this->l_forward_pin, 0);
    softPwmWrite(this->l_backward_pin, speed);
}


void Motor::backward( void ) {
    
}


void Motor::turn_left( void ) {
    
}


void Motor::turn_right( void ) {
    
}



