CC = gcc
OPTIONS = -Wall -ansi -pedantic
DEBUG_OPTIONS =
EXECUTABLE = lia

SOURCE = $(wildcard *.c)
OBJETS = $(SOURCE:.c=.o)

all: $(EXECUTABLE)

debug: DEBUG_OPTIONS = -g
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJETS)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) $(OBJETS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -MMD -c $<
