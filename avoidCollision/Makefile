#
# Felipe Kuhne
# fkuhne at gmail dot com
#

default: all

CPP = g++

CFLAGS = -Wall -I/usr/local/Aria/include
LDFLAGS = -L/usr/local/Aria/lib -lAria

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = avoidCollision

all: $(SRCS) $(EXEC)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CPP) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJS) $(EXEC)
