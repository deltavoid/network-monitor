
CXX = g++

CXX_FLAGS = -std=c++11 -Wall

CXX_INCLUDES = -I/usr/lib/llvm-3.7/include -I/usr/include/bcc

CXX_LIBS = -lbcc -lbpf -lpthread


TARGET = main

OBJECTS = main.o network_monitor.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXX_FLAGS) -o main $(OBJECTS) $(CXX_LIBS)

main.o : main.cpp network_monitor.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o main.o -c main.cpp

network_monitor.o : network_monitor.cpp network_monitor.h
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o network_monitor.o -c network_monitor.cpp

.PHONY : clean
clean :
	rm *.o 
	rm main

