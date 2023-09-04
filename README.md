# CPVector: Cross-Platform std::vector Encapsulation

CPVector is a library that provides an encapsulation for the `std::vector` class, enabling the implementation of the same functionality across various platforms in a unified manner. This library has been developed with the purpose of achieving cross-compatibility in different programming environments, while offering a familiar and user-friendly interface.

## Key Features

- **Cross-Platform Compatibility:** CPVector is designed to work on different platforms, meaning you can write code that uses the `std::vector` functionality and run it on multiple environments without worrying about implementation differences.

- **Ease of Use:** By using the same interface as `std::vector`, developers familiar with C++'s Standard Template Library (STL) will find it comfortable to work with CPVector.

- **Integration with CMake:** The directory and CMake files are included in the repository, making it easier to compile and use in larger projects.

- **Arduino Support:** CPVector has been optimized and tested for use in Arduino projects, making it an excellent choice for those seeking compatibility with this platform.

- **Clear Documentation:** The library's documentation has been generated using Doxygen, making it easier to understand the provided functions, methods, and classes by CPVector.

## Tested Platforms

CPVector has been tested on the following platforms:

- Arduino IDE:
  - AVR (e.g., Arduino Uno, Arduino Mega, etc.) ( using C )
  - ESP32 (using C, C++, and std::vector<>)

- Windows:
  - Compiled using Visual C++ (cl) (using std::vector<>)

- Ubuntu:
  - Compiled using g++ (using std::vector<>)
  - Compiled using clang++ (using std::vector<>)

- Raspbian:
  - Compiled using g++ (using std::vector<>)
  - Compiled using clang++ (using std::vector<>)

- macOS:
  - Compiled using g++ (using std::vector<>)
  - Compiled using clang++ (using std::vector<>)

## Online Documentation

CPVector features comprehensive online documentation, generated using Doxygen. This documentation provides in-depth insights into the functions, methods, classes, and usage examples offered by the library.

To access the online documentation, visit the [CPVector Documentation](https://checheromo96.github.io/CPVector_Arduino/index.html) website.

The online documentation serves as a valuable resource for understanding and effectively utilizing CPVector in your projects.

## Quick Start

To quickly get started with CPVector, follow these steps:

1. Clone the CPVector repository from [GitHub](https://github.com/ChecheRomo96/CPVector) or add the repository as a submodule in your project.

2. The main repository contains all the necessary files for various platforms and filesystems, including implementations for different platforms like Arduino, Windows, Ubuntu, and macOS.

3. Additionally, if you're specifically interested in using CPVector with CMake, you can explore the [CPVector-CMake](https://github.com/ChecheRomo96/CPVector-CMake) repository. This repository provides a directory structure and CMake files that make it easier to integrate CPVector into larger projects.

4. For Arduino-specific projects, check out the [CPVector-Arduino](https://github.com/ChecheRomo96/CPVector-Arduino) repository. This repository offers a file structure tailored for Arduino development.

By choosing the appropriate repository based on your project's requirements, you can efficiently integrate CPVector into your development environment and start benefiting from its cross-platform capabilities.


## Contributions

Your contributions are welcome! If you find issues, want to add new features, or improve existing ones, feel free to submit a pull request to the CPVector repository.

## Contact

If you have questions, suggestions, or comments, you can open an [issue](https://github.com/ChecheRomo96/CPVector/issues) on the repository.

We hope CPVector proves to be a valuable asset in your cross-platform development projects!

<!--


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


-->