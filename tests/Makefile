CC=gcc
CFLAGS= -Wall -g -MMD -coverage -D DB_PATH='"../src/model/data.db"'
LDFLAGS= -lcmocka -coverage
LDFLAGS+= `pkg-config --libs sqlite3`

ifeq ($(OS),Windows_NT)
    CFLAGS += -D OS='"Windows"'
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -D OS='"linux"'
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -D OS='"macOS"'
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
    endif
endif



all: main


main: display_helpers.o UTest.o UTest_display_helpers.o UTest_ext_files_manager.o UTest_session.o patient_manager.o session_manager.o BDD_to_struct_session.o BDD_to_struct_patient.o struct_to_BDD_patient.o struct_to_BDD_session.o extern_files_manager.o display_helpers.o
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