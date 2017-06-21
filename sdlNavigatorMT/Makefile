#
# Felipe Kuhne
# fkuhne at gmail dot com
#

default: all

CPP = g++

CFLAGS = -Wall -I/usr/local/Aria/include $(shell sdl2-config --cflags)
LDFLAGS = -L/usr/local/Aria/lib -lAria -pthread  $(shell sdl2-config --libs)

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = sdlNavigatorMT

all: $(SRCS) $(EXEC)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CPP) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJS) $(EXEC)
