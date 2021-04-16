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
***
#### For Linux

Make sure that you are up to date:
```bash
sudo apt-get update
sudo apt-get upgrade 
```

Firstly you will need to install git tools and commands:
```bash
sudo apt-get install git git -gui gitk meld pandoc
```

In order to download the project on your computer go in the folder where you want to install the project and type:
```bash
git clone "url"
```
The url can be find on the github page.

Then install the following packages:
```bash
sudo apt-get install cmake                  #for compilation
sudo apt-get install sqlite3 libsqlite3-dev #for model
sudo apt-get install libgtk-3-dev           #for UI
sudo apt-get install lcov                   #for coverage test reports
sudo apt-get install valgrind               #for memory tests
sudo apt-get install doxygen                #for documentation generation
```
if needed, add the path `/usr/lib` at the end of ld.so.conf file by doing :
```bash
sudo gedit /etc/ld.so.conf
```

You can now run the program by typing the following command at the root of the project:
```bash
chmod +x run
./run
```


#### For macOS

Firstly, if it has never been done before, you will need to install Xcode Command Line Tools to get ```gcc``` compiler and ```git```:
```bash
xcode-select --install
```
A window will prompt on your screen, follow the indications to complete installation.

In order to download the project on your computer go in the folder where you want to clone the project and type in terminal:
```bash
git clone "url"
```
The url can be find on the gitlab page.

Install ```homebrew``` if necessary:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
Then install the following packages:
```bash
brew install make cmake                 #for compilation
brew install sqlite                     #for model
brew install gtk+3                      #for UI
brew install lcov                       #for coverage test reports
brew install doxygen                    #for documentation generation
```
Valgrind is unfortunately not available for macOS. If you want to execute memory tests please use a Linux VM.

You can now run the program by typing the following command at the root of the project:
```bash
chmod +x run
./run
```

If you notice that some icons are missing, just install the missing ```gtk``` theme:
```bash
brew install adwaita-icon-theme
```

### Testing
***
See this specific [```README```](tests/README.md).

## Credits
