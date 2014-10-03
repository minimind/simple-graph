CC     = g++
CFLAGS = -Wall -O2
SRC    = unittest/main.cpp \
         unittest/graphaddtest.cpp \
         unittest/graphconstructiontest.cpp \
         unittest/graphcopytopologytest.cpp \
         unittest/graphvisitorignorekeytest.cpp \
         unittest/graphvisitortest.cpp

TARGET = test_graph

OBJ = $(SRC:.cpp=.o)

all:	$(TARGET)

$(TARGET):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
