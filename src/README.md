# mpags-cipher
A simple command line tool for encrypting/decrypting text using classical ciphers

## Authors
Thomas Latham, Ben Morgan, Mark Slater, Matt Williams, Luke Kreczko

## Building `mpags-cipher`
Compilation of `mpags-cipher` requires a  C++11 compatible compiler
(GCC 8 or better, Clang 8 or better are recommended) on a UNIX operating
system.
Windows platforms with Visual Studio 2015 or better are also expected to
work, but not tested.

To build from a clone of this repository, open a terminal window
and change directory into that holding this README. Then run:
```
$ ls
MPAGSCipher/       CMakeLists.txt        LICENSE          README.md        mpags-cipher.cpp  
$ g++ -std=c++11 -Wall -Wextra -Werror -Wfatal-errors -pedantic -Wshadow -o mpags-cipher mpags-cipher.cpp
$ ./mpags-cipher
```

or 

```
$ ls
MPAGSCipher/       CMakeLists.txt        LICENSE          README.md        mpags-cipher.cpp  
$ make
$ ./mpags-cipher
```

If no input file is supplied, `mpags-cipher` will wait for user input
from the keyboard until RETURN followed by CTRL-D are pressed.
To ensure the input text can be used with the character sets known to
classical ciphers, it is transliterated using the following rules:

- Alphabetical characters are converted to uppercase
- Digits are translated to their English equivalent words (e.g. '0' -> "ZERO")
- All other characters (punctuation) are discarded

The results of this transliteration are output after CTRL-D.

## Source code layout
```
.
├── MPAGSCipher/                      Subdirectory for storing functions and header files
    ├── ProcessCmdLine.cpp            ProcessCmdLine function C++ source file
    ├── ProcessCmdLine.hpp            ProcessCmdLine header file
    ├── RunCaesarCipher.cpp           Caesar cipher encryption and decryption function C++ source file
    ├── RunCaesarCipher.hpp           Caesar cipher function header file
    ├── TransformChar.cpp             TransformChar function C++ source file
    └── TransformChar.hpp             TransformChar header file
├── CMakeLists.txt                    CMake file
├── LICENSE                           License file, in our case MIT
├── mpags-cipher.cpp                  Main program C++ source file
└── README.md                         This file, describes the project
```

## Copying
`mpags-cipher` is licensed under the terms of the MIT License.
Please see the file [`LICENSE`](LICENSE) for full details.