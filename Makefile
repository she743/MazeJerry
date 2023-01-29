SRC_DIR = ./src
OBJ_DIR = ./obj

CC = g++
TARGET = main

SRCS = $(notdir $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(SRCS:.cpp=.o)
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)

LIBRARIES = -lwiringPi -lpthread


all: $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	mkdir $(OBJ_DIR) 2> /dev/null || true
	$(CC) -c $< -o $@ -MD 

$(TARGET) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET).out $(LIBRARIES)

.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)

-include $(DEPS)