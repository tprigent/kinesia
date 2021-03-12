CC=gcc
CFLAGS= -Wall -MMD -coverage -D DB_PATH='"model/data.db"'
LDFLAGS= -lcmocka -coverage
LDFLAGS+= `pkg-config --libs sqlite3`

all: main


main: connect_struct_UI.o UTest.o UTest_UI.o patient.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< $^

cov_test: main
	./main ; \
    lcov --capture --directory . --output-file coverage.info ; \
    genhtml coverage.info --output-directory covreport ; \

mem_test: main
	./main ; \
    valgrind --log-file="memreport" --leak-check=yes ./$^

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