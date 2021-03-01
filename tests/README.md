## Table of Contents
1. [General info](#general-info)
2. [Get started](#get-started)
3. [Run tests](#run-tests)
    1. [Unit tests](#unit-tests)
    2. [Coverage test](#coverage-test)
    3. [Memory check](#memory-check)

### General Info

In this folder  you will find every files required to run:
- unit tests (using CMocka)
- coverage tests (using Gcov & Lcov)
- memory tests (using Valgrind)

A script is provided to run all of those tests.

## Get started

The first time you download this project you must add permission to execute run_tests with the following command:
```bash
chmod +x run_tests
```

## Run tests
To run the test, make sure you are in the ```tests/``` folder, then execute:
```bash
./run_tests
```
A message will ask you for a confirmation, type ```y``` if everything is correct.
<br/><br/>

#### Unit Tests
During the script, chose ```u``` to launch unit tests via the ```CMakeList.txt```.

CMocka software will be temporary downloaded from [source repository](https://git.cryptomilk.org/projects/cmocka.git). This may take a while.

In the end, a log file named ```unitreport-yyyy-mm-dd-hh-mm-ss.log``` will be placed in ```tests/```.
<br/><br/>

#### Coverage test
During the script, chose ```c``` to launch coverage and memory tests.

Elements needed will be compiled by the ```Makefile```.

HTML coverage report will be created in ```tests/coverage/```.

#### Memory check
During the script, chose ```m``` to launch coverage and memory tests.

Elements needed will be compiled by the ```Makefile```.

Memory leaks report will be created in ```tests/memreport-yyyy-mm-dd-hh-mm-ss.log```.
