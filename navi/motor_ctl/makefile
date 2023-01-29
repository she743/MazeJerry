FILE = motor
CPP = cpp
OBJ = o

LIB_WPI = lwiringPi
LIB_PTH = lpthread

OBJECT_DIR = ../obj
OBJECTS = $(OBJECT_DIR)/$(FILE).$(OBJ)


main: lib $(OBJECTS) 
	g++ -o a.out _motor_ctl_test.cpp $(OBJECTS) -$(LIB_WPI) -$(LIB_PTH)

lib:
	g++ -c $(FILE).$(CPP)

clean:
	rm a.out
	rm $(FILE).$(OBJ)