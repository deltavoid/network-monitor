
CXX = g++

CXX_FLAGS = -std=c++11 -Wall

CXX_INCLUDES = -I/usr/lib/llvm-3.7/include -I/usr/include/bcc

CXX_LIBS = -lbcc


TARGET = HelloWorld

$(TARGET) : $(TARGET).o
	$(CXX) $(CXX_FLAGS) -o $(TARGET) $(TARGET).o $(CXX_LIBS)

$(TARGET).o : $(TARGET).cc
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) -o $(TARGET).o -c $(TARGET).cc

.PHONY : clean
clean :
	rm $(TARGET).o
	rm $(TARGET)