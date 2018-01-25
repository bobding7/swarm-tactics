RM = rm -rf
O_SRCS = tsp.o 
CPP_SRCS = main.cpp tsp.cpp twoOpt.cpp
OBJS = main.o tsp.o twoOpt.o
CPP_DEPS = main.d tsp.d twoOpt.d 
LIBS = -lm -L/usr/include -lpthread

%.o: %.cpp
	g++ -g -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

tsp: $(OBJS)
	g++  -o "tsp" $(OBJS) $(LIBS) 

all: tsp

clean:
	rm tsp *.o *.d
	rm -f *.tour
	
