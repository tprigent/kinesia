## Table of Contents
1. [General Info](#general-info)
2. [Installation](#installation)
3. [Run tests](#run-tests)

### General Info
***
In the folder tests you will find every files required to run the Unit Tests and the code coverage.

## Installation
***
The installation requires to download CMocka files. All the commands needed for the installation have already been written in an executable file name run_tests.

The first time you download this project you must add permission to execute run_tests with the followind command
```
$ chmod +x run_tests
```

## Run tests
***
To run the test you need to be in the folder tests, then execute
```
$ ./run_tests
```
This command will download all the necessary files from the site https://git.cryptomilk.org/projects/cmocka.git, generate a file named report-{DATE}.log in tests which contains the result of the unit tests and automaticaly clean the repository.
