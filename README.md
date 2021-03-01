# Kinesia

Kinesia is a free and open-source software for physiotherapists.
It allows them to easily manage patient information and consultation notes.

## Table of Contents
1. [For users](#for-users)
2. [Join the project](#join-the-project)
    1. [Installation](#installation)
    2. [Testing](#testing)
3. [Credits](#credits)

## For users

// To be written

## Join the project

To build and run the project you will need to install several tools.

### Installation
#### For Linux

Make sure that you're up to date:
```bash
sudo apt-get update
sudo apt-get upgrade 
```
Then install the following packages:
```bash
sudo apt-get cmake                          #for compilation
sudo apt-get install sqlite3 libsqlite3-dev #for database
sudo apt-get install libgtk-3-dev           #for UI
sudo apt-get install lcov                   #for coverage test reports
sudo apt-get install valgrind               #for memory tests
```

#### For macOS

Install ```homebrew``` if necessary:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
Then install the following packages:
```bash
brew install cmake                      #for compilation
brew install sqlite                     #for database
brew install gtk+3                      #for UI
brew install lcov                       #for coverage test reports
```
Valgrind is unfortunately not available for macOS. If you want to execute memory tests please use a Linux VM.

### Testing
See this specific [```README```](https://gitlab.insa-rennes.fr/tprigent/projet-logiciel-kine/-/blob/cov_integration/tests/README.md).

## Credits
