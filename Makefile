# compiler
CC = gcc
#compiler flags
CFLAGS = -Wall -Wextra -Werror -pedantic -std=gnu89 -IUnity
UNITY_CFLAGS = -Wall -Wextra -Werror -pedantic -std=gnu99 -IUnity

#directories
BUILD = build
OBJDIR = obj
HOLBERTON_DIR = holberton

#holberton main files
MAIN_SRCS = $(wildcard $HOLBERTON_DIR/*-main.c)
MAIN_BINS = $(patsubst %.c, $(BUILD)/%, $(notdir $(MAIN_SRCS)))

#custom main.c
MY_MAIN_BIN = $(BUILD)/my_main

#.c files and .o files
#main.c and -main.c
SRC_ALL = $(wildcard *.c)
SRC = $(filter-out %-main.c main.c, $(SRC_ALL))
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

#unity .c and .o files
UNITY_OBJ = $(OBJDIR)/unity.o
UNITY_SRC = Unity/unity.c

#tests .c and .o files
TESTS = $(wildcard tests/test_*.c)
TEST_BINS = $(strip $(patsubst tests/%.c, $(BUILD)/%, $(TESTS)))

#capture stdout .c and .o files
CAPTURE_SRC = tests/capture_stdout.c tests/capture_stderr.c
CAPTURE_OBJS = $(patsubst tests/%.c, $(OBJDIR)/%.o, $(CAPTURE_SRC))

.PHONY: all clean test run-tests run-% help valgrind-tests

all: $(MAIN_BINS) $(MY_MAIN_BIN) test

#generate test if they exist binaries if .c exist
test:
	@if [ -z "$(TESTS)" ]; then \
		echo "⚠️  No test files found. Only built main binaries."; \
	else \
		$(MAKE) run-tests; \
	fi

#run tests
run-tests: $(TEST_BINS)
	@for bin in $(TEST_BINS); do \
		echo "Running $$bin..."; \
		if ./$$bin; then \
			echo "✅ $$bin passed"; \
		else \
			echo "❌ $$bin failed"; \
			exit 1; \
		fi; \
	done

#run tests with valgrind
valgrind-tests: $(TEST_BINS)
	@echo "🔍 Running tests under Valgrind..."
	@for bin in $(TEST_BINS); do \
		echo "🔎 Testing $$bin with Valgrind..."; \
		if valgrind --leak-check=full --error-exitcode=1 ./$$bin; then \
			echo "✅ $$bin passed (no leaks detected)"; \
		else \
			echo "❌ $$bin failed under Valgrind"; \
			exit 1; \
		fi; \
	done

#generating binaries for main
$(BUILD)/%: $(HOLBERTON_DIR)/%-main.c $(OBJS) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

#generate binaries for main.c
$(MY_MAIN_BIN): $(OBJDIR)/main.o $(OBJS) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

# build test binaries
$(BUILD)/%: tests/%.c $(OBJS) $(UNITY_OBJ) $(CAPTURE_OBJS) | $(BUILD)
	$(CC) $(UNITY_CFLAGS) $^ -o $@

#generating .o files for unity
$(UNITY_OBJ): $(UNITY_SRC) | $(OBJDIR)
	$(CC) $(UNITY_CFLAGS) -c $< -o $@

#generating .o files in obj/
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

#generate .o files from tests
$(OBJDIR)/%.o: tests/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

#generating main.o file
$(OBJDIR)/main.o: main.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

#specific test run
run-%: $(BUILD)/%
	./$<

#create a obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

#create build directory if it doesn't exist
$(BUILD):
	mkdir -p $(BUILD)

#delete the binary directory if it doesn't exist
clean:
	rm -rf $(BUILD) $(OBJDIR)

help:
	@echo "Available targets:"
	@echo "  all    - Build all binaries"
	@echo "  clean  - Remove build files"
	@echo "  test   - Run unit tests"
	@echo "  run-%  - Run a specific test"
	@echo "  valgrind-tests - Run all tests under Valgrind"

print-tests:
	@echo "TESTS: $(TESTS)"
	@echo "TEST_BINS: $(TEST_BINS)"
