CC = gcc
CFLAGS = -Wall

BUILD_DIR = build/

SOURCES = \
		src/cli.c\
		src/epsilon.c\
		src/flag.c\
		src/io.c\
		src/list.c\
		src/main.c\
		src/matrix.c\
		src/options.c\
		src/point.c\
		src/point_list.c\
		src/polynomial.c\
		src/spline.c
OBJECTS = $(SOURCES:%.c=%.o)
EXECUTABLE = splines

SOURCES_TESTS =\
    src/test/cli.c\
    src/test/io.c\
    src/test/matrix.c\
    src/test/minunit.c\
    src/test/spline.c
OBJECTS_TESTS = $(SOURCES_TESTS:%.c=%.o)
EXECUTABLE_TESTS = $(EXECUTABLE)_test

all: $(SOURCES) $(EXECUTABLE)
	mv $(EXECUTABLE) $(BUILD_DIR)

all_tests: $(SOURCES) $(SOURCES_TESTS) $(EXECUTABLE_TESTS)
	mv $(EXECUTABLE_TESTS) $(BUILD_DIR)

test: all_tests
	cd $(BUILD_DIR) && ./$(EXECUTABLE_TESTS)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

$(EXECUTABLE_TESTS): $(OBJECTS) $(OBJECTS_TESTS)
	$(CC) $(filter-out src/main.o, $(OBJECTS)) $(OBJECTS_TESTS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(OBJECTS_TESTS) $(EXECUTABLE_TESTS)
