FILE = sensing
CPP = cpp
OBJ = o

LIB_WPI = lwiringPi
LIB_PTH = lpthread

OBJECT_DIR = ../obj
OBJECTS = $(OBJECT_DIR)/$(FILE).$(OBJ)


main: lib $(OBJECTS) 
	g++ -o a.out _sensing_test.$(CPP) $(OBJECTS)  -$(LIB_WPI)

lib:
	g++ -c $(FILE).$(CPP)
	mv $(FILE).$(OBJ) $(OBJECT_DIR)/

clean:
	rm a.out
	rm $(FILE).$(OBJ)