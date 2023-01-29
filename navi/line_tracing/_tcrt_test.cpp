#include "tcrt.h"
#include <iostream>

using namespace std;
using namespace Tcrt;

int main() {
    int l_sensor_pin = 0;
    int m_sensor_pin = 2;
    int r_sensor_pin = 3;

    Line_Sensor lines(l_sensor_pin, m_sensor_pin, r_sensor_pin);
    LineDataFrame data = lines.get();
    cout << data.left_d << data.middle_d << data.right_d << endl;
    lines.cleanup();

    return 0;
}