from typing import *


class SensorData:
    l_data: int
    f_data: int
    r_data: int
    def __init__(self, data: List[int]) -> None:
        self.l_data = data[0]
        self.f_data = data[1]
        self.r_data = data[2]

    def __repr__(self) -> str:
        return f"[{self.l_data}, {self.f_data}, {self.r_data}]"


class Sensor:
    def __init__(self, pins: List[int]) -> None:
        self.l_sensor_pin = pins[0]
        self.f_sensor_pin = pins[1]
        self.r_sensor_pin = pins[2]

        '''
            Please add WiringPi codes, Here!
            Examples::
                >>> import wiringpi
                >>> ...
                >>> wiringpi.wiringPiSetup()
        '''

    def get(self) -> SensorData:
        '''
            Please add WiringPi codes, Here!
            Examples::
                >>> import wiringpi
                >>> ...
                >>> wiringpi.digitalRead(self.l_sensor_pin)
        '''
        l_sensor_data = ...
        f_sensor_data = ...
        r_sensor_data = ...
        return SensorData( [l_sensor_data, f_sensor_data, r_sensor_data] )

