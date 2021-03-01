CC=gcc
CFLAGS= -Wall -MMD -coverage
LDFLAGS= -lcmocka -coverage


all: main

main: connect_struct_UI.o UTest.o UTest_UI.o patient.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< $^

run_test: main
	./main ; \
    lcov --capture --directory . --output-file coverage.info ; \
    genhtml coverage.info --output-directory ../tests/coverage ; \
    valgrind ./$<


clean:
	rm -f *.o
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.d
	rm -f coverage.info
	rm -f main


process:
	make clean
	make
	./main