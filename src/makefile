# Joe Jevnik
# 15.10.2013

CC=gcc
CFLAGS=-c -std=c11 -Wall -O2
LDFLAGS=
SOURCES=main.c typing.c screen.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=doge

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lncurses -lpthread

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)
