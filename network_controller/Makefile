

CXX = g++

#LIBDIR ?= ../lib/headers

CXXFLAGS = -g -Wall -O2 -std=c++11 #-I$(LIBDIR)

LDFLAGS = -pthread

TARGET = main

OBJECTS = main.o network_controller.o network_driver.o network_monitor.o


LLVM_PATH="/usr/lib/llvm-3.7"

BCC_PATH="/home/zqy/WorkSpace/LabeledKernel/Reference/linux/eBPF/bcc"



all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o main
	@echo [INFO] Compilation accomplished.

main.o: main.cpp network_controller.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ -c $< 

network_controller.o: network_controller.cpp network_driver.h network_monitor.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ -c $<

network_driver.o: network_driver.cpp network_driver.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ -c $<

network_monitor.o: network_monitor.cpp network_monitor.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	@-rm *.o
	@-rm main
	@echo [INFO] Clean accomplished.


