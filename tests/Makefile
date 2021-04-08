CC=gcc
CFLAGS= -Wall -g -MMD -coverage -D DB_PATH='"database/Bdd.db"'
LDFLAGS= -lcmocka -coverage
LDFLAGS+= `pkg-config --libs sqlite3`

all: main


main: display_helpers.o UTest.o UTest_UI.o UTest_session.o UTest_BDD_session.o UTest_BDD.o patient_manager.o session_manager.o BDD_to_struct_session.o BDD_to_struct_patient.o struct_to_BDD_patient.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< $^

%.o: ../src/controller/%.c
	$(CC) -c $(CFLAGS) $< $^

%.o: ../src/model/%.c
	$(CC) -c $(CFLAGS) $< $^

cov_test: main
	./main ; \
    lcov --capture --directory . --output-file coverage.info ; \
    genhtml coverage.info --output-directory covreport ; \

mem_test: main
	./main ; \
    valgrind --log-file="memreport" --leak-check=full --track-origins=yes ./$^

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