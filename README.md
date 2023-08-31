# Cross-Platform Vector

The intention of CPVector is to unify vector (dynamic size arrays) classes across multiple systems. CPVector::vector<> is based on std::vector<> class and implements some of its functionality.

These library contains a CMake build generation system. You can install the package with cmake to make it available in your system, also you can "add" this repository as a subdirectory with cmake to compile the library when building your project.

This library also complies with the Arduino Library Specification. To achieve this, a library.properties file has been included. Also there is a keywords.txt file so the IDE knows how to color keywords, examples are in the directory examples. The exaples are automatically discovered by Arduino IDE due to the file structure. Examples can also be compiled via cmake by adding the cache variable CPVECTOR_BUILD_EXAMPLES = ON.

List of platforms where it has been tested.

- Arduino IDE (AVR, ESP32)
- Windows (cl)
- Ubuntu (g++, clang++)
- Mac Os (g++, clang++)

# Documentation:

There is a web page documentation available, This project's documentation has been created using Doxygen, a powerful documentation generator tool. Doxygen allows for the automatic generation of comprehensive documentation by extracting and analyzing code comments, providing developers a clear and structured overview of the project's functionalities, APIs, and internal workings.

Docs hosted at: https://checheromo96.github.io/CPVector/

# Introduction

## Instalation

The instalation process may be different for diferent systems. Please check the <a href="https://checheromo96.github.io/CPVector/d9/d8d/_instalation.html">Installation Page</a> for a more detailed explanation for multiple systems.

# Steps to compile package:

## Mac Os X through CMake + make

1.- Clone or download the repo.

2.- Open terminal and go to the the download directory (Replace "<path_to_directory>" with the path to the directory you downloaded) 

    cd <path_to_directory>/CPVector

3.- Run 

	mkdir build && cd build

4.1.- To compile run: 
	
	cmake ..

4.2.- To compile examples and turn them into executables, run: 
	
	cmake .. -DBUILD_EXAMPLES="ON"

5.- Run 
	
	make	
	sudo make install

# Steps to uninstall package:

## Mac Os X

1.- Remove the following directories

	usr/local/lib/CPString
	usr/local/include/CPString

