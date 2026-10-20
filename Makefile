CC = gcc
OPTIONS = -Wall -std=c17 -pedantic -Wextra
DEBUG_OPTIONS =
EXECUTABLE = lia

CLEANUP = rm -f
MKDIR = mkdir -p
DEPEND = -MM -MG -MF
# For result files
TARGET_EXTENSION = out

LDLIBS = -lm

# Avoid launching every targets that are not files
.PHONY: all debug clean test

# Paths
PATHUNITY = test/vendor/Unity/src/
PATHSRC = src/
PATHTEST = test/
PATHBUILD = build/
PATHOBJECT = build/object/
PATHDEP = build/dependency/
PATHRESULTS = build/result/

BUILD_PATHS = $(PATHBUILD) $(PATHOBJECT) $(PATHDEP) $(PATHRESULTS)

# Building
SOURCE = $(wildcard *.c)
OBJETS = $(SOURCE:.c=.o)
DEPENDANCES = $(SOURCE:.c=.d)

# Testing
SOURCETEST = $(wildcard $(PATHTEST)*.c)
CFLAGS = -I. -I$(PATHUNITY) -I$(PATHSRC) -DTEST

RESULTS = $(patsubst $(PATHTEST)Test%.c, $(PATHRESULTS)Test%.txt, $(SOURCETEST))
$(PATHRESULTS)%.txt: $(PATHBUILD)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

# Default target
all: $(EXECUTABLE)

# Debug target
# Gives advice on dirty things in the code
debug: DEBUG_OPTIONS = -fsanitize=address -g
# Depends on clean to avoid object related issues
debug: clean $(EXECUTABLE)

# Clean target
clean:
	$(CLEANUP) $(EXECUTABLE)
	$(CLEANUP) $(PATHOBJECT)*.o
	$(CLEANUP) $(PATHDEP)*.d
	$(CLEANUP) $(PATHBUILD)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHRESULTS)*.txt

# Test target
test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES\n-----------------------"
	@echo `grep -s IGNORE $(PATHRESULTS)*.txt`
	@echo "-----------------------\nFAILURES\n-----------------------"
	@echo `grep -s FAIL $(PATHRESULTS)*.txt`
	@echo "\nDONE"

# Creating test executable
$(PATHBUILD)Test%.$(TARGET_EXTENSION): $(PATHOBJECT)Test%.o $(PATHOBJECT)unity.o
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -o $@ $(filter %.o, $^) $(LDLIBS)

# Creating object files
$(PATHOBJECT)%.o:: $(PATHTEST)%.c
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -c $(CFLAGS) $< -o $@

$(PATHOBJECT)%.o:: $(PATHSRC)%.c
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -c $(CFLAGS) $< -o $@

$(PATHOBJECT)%.o:: $(PATHUNITY)%.c $(PATHUNITY)%.h
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -c $(CFLAGS) $< -o $@

# Creating dependencies
$(PATHDEP)%.d:: $(PATHTEST)%.c
	$(DEPEND) $@ $<

# Creating Executable (other than test)
$(EXECUTABLE): $(OBJETS)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) $(OBJETS) -o $(EXECUTABLE) $(LDLIBS)

%.o: %.c
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -MMD -c $<

# Create directories if they don't exist
$(BUILD_PATHS):
	$(MKDIR) $@

.PRECIOUS: $(PATHBUILD)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHDEP)%.d
.PRECIOUS: $(PATHOBJECT)%.o
.PRECIOUS: $(PATHRESULTS)%.txt

-include $(DEPENDANCES) # Include .d files into Makefile
