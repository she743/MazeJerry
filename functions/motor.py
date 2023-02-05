from typing import *


class Motor:
    def __init__(self, pins: List[int]) -> None:
        self.r_fpin = pins[0]
        self.r_bpin = pins[1]
        self.l_fpin = pins[2]
        self.l_bpin = pins[3]

        '''
            Please add WiringPi codes, Here!
            Examples::
                >>> import wiringpi
                >>> ...
                >>> wiringpi.wiringPiSetup()
        '''

    def forward(self):
        '''
            Examples::
                >>> import wiringpi
                >>> wiringpi.softPwmWrite(pin, speed)
                >>> wiringpi.delay(delay)
        '''
        ...

    def backward(self):
        '''
            Turn right > Turn right > Forward
        '''
        ...

    def left(self):
        ...

    def right(self):
        ...

