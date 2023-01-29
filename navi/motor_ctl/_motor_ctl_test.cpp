#include "motor.h"
#include <iostream>

using namespace std;
using namespace MotorCTL;


int main() {
    Instruct inst = {20, true};

    Motor motors( 1, 26, 23, 24 );
    motors.move( inst );
    motors.cleanup();

    return 0;
}