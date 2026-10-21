CC = gcc
OPTIONS = -Wall -std=c17 -pedantic -Wextra
DEBUG_OPTIONS =
EXECUTABLE = lia

CLEANUP = rm -f
MKDIR = mkdir -p
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
PATHRESULTS = build/result/

BUILD_PATHS = $(PATHBUILD) $(PATHOBJECT) $(PATHRESULTS)

# Building
SOURCE = $(wildcard $(PATHSRC)*.c)
OBJETS = $(patsubst $(PATHSRC)%.c, $(PATHOBJECT)%.o, $(SOURCE))

# Testing
SOURCETEST = $(wildcard $(PATHTEST)*.c)
CFLAGS = -I. -I$(PATHUNITY) -I$(PATHSRC)

RESULTS = $(patsubst $(PATHTEST)Test%.c, $(PATHRESULTS)Test%.txt, $(SOURCETEST))
$(PATHRESULTS)%.txt: $(PATHBUILD)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

# Default target
all: $(EXECUTABLE) | $(PATHRESULTS)

# Debug target
# Gives advice on dirty things in the code
debug: DEBUG_OPTIONS = -fsanitize=address -g
# Depends on clean to avoid object related issues
debug: clean $(EXECUTABLE)

# Clean target
clean:
	$(CLEANUP) $(EXECUTABLE)
	$(CLEANUP) $(PATHOBJECT)*.o
	$(CLEANUP) $(PATHOBJECT)*.d
	$(CLEANUP) $(PATHBUILD)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHRESULTS)*.txt

# Test target
test: $(RESULTS)
	@echo "-----------------------\nIGNORES\n-----------------------"
	@echo `grep -s IGNORE $(PATHRESULTS)*.txt`
	@echo "-----------------------\nFAILURES\n-----------------------"
	@echo `grep -s FAIL $(PATHRESULTS)*.txt`
	@echo "\nDONE"

# Creating test executable
$(PATHBUILD)Test%.$(TARGET_EXTENSION): $(PATHOBJECT)Test%.o $(PATHOBJECT)%.o $(PATHOBJECT)unity.o | $(PATHBUILD)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -o $@ $(filter %.o, $^) $(LDLIBS)

# Creating object files
$(PATHOBJECT)%.o:: $(PATHTEST)%.c | $(PATHOBJECT)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -c -MMD -MP $(CFLAGS) $< -o $@

$(PATHOBJECT)%.o:: $(PATHSRC)%.c | $(PATHOBJECT)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -c -MMD -MP $(CFLAGS) $< -o $@

$(PATHOBJECT)%.o:: $(PATHUNITY)%.c $(PATHUNITY)%.h | $(PATHOBJECT)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) -c -MMD -MP $(CFLAGS) $< -o $@

# Creating Executable (other than test)
$(EXECUTABLE): $(OBJETS)
	$(CC) $(DEBUG_OPTIONS) $(OPTIONS) $^ -o $@ $(LDLIBS)

# Create directories if they don't exist
$(BUILD_PATHS):
	$(MKDIR) $@

.PRECIOUS: $(PATHBUILD)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHOBJECT)%.o
.PRECIOUS: $(PATHRESULTS)%.txt

# Include .d files into Makefile
-include $(wildcard $(PATHOBJECT)*.d)
