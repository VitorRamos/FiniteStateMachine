CXX = g++
CPPFLAGS = -Wall -O3 -std=c++11 -I include/

all: main

main: main.cpp states.cpp stateMachine.cpp

.PHONY: clean realclean 

clean:
	-rm -f *.o *~ 
	-rm main


