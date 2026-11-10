CC = gcc
CFLAGS = -Wall -std=c17 -pedantic -Wextra -O2
DEBUG_OPTIONS =
EXECUTABLE = lia

CLEANUP = rm -f
MKDIR = mkdir -p
# For result files
TARGET_EXTENSION = out
BUILD ?= release

LDLIBS = -lm

# Avoid launching every targets that are not files
.PHONY: all debug clean test format format-check analyze

# Paths
PATHUNITY = test/vendor/Unity/src/
PATHSRC = src/
PATHTEST = test/
PATHBUILD = build/
PATHOBJECT = build/$(BUILD)/object/
PATHRESULTS = build/result/

BUILD_PATHS = $(PATHBUILD) $(PATHOBJECT) $(PATHRESULTS)

# Building
SOURCE = $(wildcard $(PATHSRC)*.c)
OBJETS = $(patsubst $(PATHSRC)%.c, $(PATHOBJECT)%.o, $(SOURCE))

# Testing
SOURCETEST = $(wildcard $(PATHTEST)*.c)
CPPFLAGS = -Iinclude -I$(PATHUNITY) -DUNITY_INCLUDE_DOUBLE

# Formating
FORMAT = $(wildcard $(PATHSRC)*.c $(PATHTEST)*.c include/*.h)

RESULTS = $(patsubst $(PATHTEST)Test%.c, $(PATHRESULTS)Test%.txt, $(SOURCETEST))
$(PATHRESULTS)%.txt: $(PATHBUILD)%.$(TARGET_EXTENSION)
	./$< > $@ 2>&1 || (cat $@; exit 1)

# Default target
all: $(EXECUTABLE) | $(PATHRESULTS)

# Debug target
debug:
	$(MAKE) BUILD=debug DEBUG_OPTIONS="-fsanitize=address -g"

# Analyze target - static analysis, debug without running
analyze: clean
	scan-build --status-bugs $(MAKE) CC=clang $(EXECUTABLE)

# Clean target
clean:
	$(CLEANUP) $(EXECUTABLE)
	$(CLEANUP) $(PATHOBJECT)*.o
	$(CLEANUP) $(PATHOBJECT)*.d
	$(CLEANUP) $(PATHBUILD)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHRESULTS)*.txt

# Test target
test: $(RESULTS)
	@echo "\nNO FAILLURE\n"

# Format targets - Used to format all files using clang (check is used by CI)
format:
	clang-format -i $(FORMAT)

format-check:
	clang-format --dry-run --werror $(FORMAT)

# Creating test executable
$(PATHBUILD)Test%.$(TARGET_EXTENSION): $(PATHOBJECT)Test%.o $(filter-out $(PATHOBJECT)Main.o,$(OBJETS)) $(PATHOBJECT)unity.o | $(PATHBUILD)
	$(CC) $(DEBUG_OPTIONS) $(CFLAGS) -o $@ $(filter %.o, $^) $(LDLIBS)

# Creating object files
$(PATHOBJECT)%.o:: $(PATHTEST)%.c | $(PATHOBJECT)
	$(CC) $(DEBUG_OPTIONS) $(CFLAGS) -c -MMD -MP $(CPPFLAGS) $< -o $@

$(PATHOBJECT)%.o:: $(PATHSRC)%.c | $(PATHOBJECT)
	$(CC) $(DEBUG_OPTIONS) $(CFLAGS) -c -MMD -MP $(CPPFLAGS) $< -o $@

$(PATHOBJECT)%.o:: $(PATHUNITY)%.c $(PATHUNITY)%.h | $(PATHOBJECT)
	$(CC) $(DEBUG_OPTIONS) $(CFLAGS) -c -MMD -MP $(CPPFLAGS) $< -o $@

# Creating Executable (other than test)
$(EXECUTABLE): $(OBJETS)
	$(CC) $(DEBUG_OPTIONS) $(CFLAGS) $^ -o $@ $(LDLIBS)

# Create directories if they don't exist
$(BUILD_PATHS):
	$(MKDIR) $@

.PRECIOUS: $(PATHBUILD)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHOBJECT)%.o
.PRECIOUS: $(PATHRESULTS)%.txt

# Include .d files into Makefile
-include $(wildcard $(PATHOBJECT)*.d)
