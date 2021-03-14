CC=gcc
CFLAGS= -Wall -MMD -coverage -D DB_PATH='"database/Bdd.db"'
LDFLAGS= -lcmocka -coverage
LDFLAGS+= `pkg-config --libs sqlite3`

all: main


main: struct_to_UI.o UI_to_struct.o UTest.o UTest_UI.o UTest_BDD.o patient.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< $^

struct_to_UI.o: ../src/controler/struct_to_UI.c
	$(CC) -c $(CFLAGS) $< $^

patient.o: ../src/patient.c
	$(CC) -c $(CFLAGS) $< $^

UI_to_struct.o: ../src/controler/UI_to_struct.c
	$(CC) -c $(CFLAGS) $< $^

cov_test: main
	./main ; \
    lcov --capture --directory . --output-file coverage.info ; \
    genhtml coverage.info --output-directory covreport ; \

mem_test: main
	./main ; \
    valgrind --log-file="memreport" --leak-check=yes --track-origins=yes ./$^

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