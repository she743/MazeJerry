#include "motor.h"
#include <iostream>
#include "wiringPi.h"

using namespace std;
using namespace MotorCTL;


int main() {
    Motor motors( 1, 26, 23, 24 );
    motors.forward();
    delay(1000);
    motors.stop();
    delay(500);
    motors.turn_left();
    delay(1000);
    motors.stop();
    delay(500);
    motors.turn_right();
    delay(1000);
    motors.stop();
    delay(500);
    motors.cleanup();
    return 0;
}