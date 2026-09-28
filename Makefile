CC = gcc
OPTIONS = -Wall -ansi -pedantic
DEBUG_OPTIONS =
EXECUTABLE = lia
LDLIBS = -lm

SOURCE = $(wildcard *.c)
OBJETS = $(SOURCE:.c=.o)

all: $(EXECUTABLE)

debug: DEBUG_OPTIONS = -g
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJETS)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) $(OBJETS) -o $(EXECUTABLE) $(LDLIBS)

%.o: %.c
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -MMD -c $<
