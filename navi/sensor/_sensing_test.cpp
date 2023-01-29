#include "sensing.h"
#include <iostream>

using namespace std;
using namespace Sensing;


int main() {
    int l_sensor_pin = 21;
    int f_sensor_pin = 22;
    int r_sensor_pin = 24;

    Sensor sensors( l_sensor_pin, f_sensor_pin, r_sensor_pin );
    SensorDataFrame data = sensors.get();
    cout << data.l_data << data.f_data << data.r_data << endl;
    sensors.cleanup();

    return 0;
}