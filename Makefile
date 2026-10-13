CC = gcc
OPTIONS = -Wall -std=c17 -pedantic -Wextra
DEBUG_OPTIONS =
EXECUTABLE = lia
LDLIBS = -lm

SOURCE = $(wildcard *.c)
OBJETS = $(SOURCE:.c=.o)
DEPENDANCES = $(SOURCE:.c=.d)

CLEANABLE = *.o $(EXECUTABLE) *.d

# Default target
all: $(EXECUTABLE)

# Debug target
debug: DEBUG_OPTIONS = -fsanitize=address -g
debug: clean $(EXECUTABLE) # Depends on clean to avoid object related issues

# Clean target
clean:
	rm -f $(CLEANABLE)

$(EXECUTABLE): $(OBJETS)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) $(OBJETS) -o $(EXECUTABLE) $(LDLIBS)

%.o: %.c
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -MMD -c $<

-include $(DEPENDANCES) # Include .d files into Makefile
