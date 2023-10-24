//C++ functions
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//user defined functions
#include "TransformChar.hpp"    //makes characters capitalised 
#include "ProcessCmdLine.hpp"   //processes the cmdline arguments
#include "RunCaesarCipher.hpp"  //caesar cipher


int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    bool encrypt{false};
    bool decrypt{false};
    bool keysupplied{false};
    int key{0};

    bool processed{processCmdLine(cmdLineArgs,helpRequested,versionRequested,inputFile,outputFile,encrypt,decrypt,keysupplied,key)};
   //pass command line arguments through the processCmdLine function

    if(!processed){
    return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText{""};
    std::string readinText{""}; //string to process text from input file
    std::string outText{""};

    // Read in user input from stdin/file
    if (!inputFile.empty()) {   //if input file is not empty on cmd line arguments
        std::ifstream in_file{inputFile};   //setup an ifstream of the inputfile name
        bool readinok = in_file.good(); //setup bool to check if readin is ok
        if(readinok){   //if readin is true -- i.e. we can readin from the file supplied to the cmd line 
            in_file >> readinText;  //store input from file in readinText
            for(std::size_t j{0}; j < readinText.length(); ++j){    //loop over each character in the string
                inputChar = readinText[j];  //assign the character to inputChar
                inputText += transformChar(inputChar);  //append to inputText
            }
            if(encrypt or decrypt) {    //if encryption or decryption is specified act on this
                inputText = runCaesarCipher(inputText,key,encrypt,decrypt); //apply encryption or decryption to inputText
            }
            inputText += "\n";  //add \n to end of inputText to start a new line in the console and output file
        } else {    
            std::cerr << "[Warning] cannot read in from file ('" << inputFile   //if the file cannot be read from then output no zero return
                      << "')\n";
            return 1;
        }
    } else {    //if there is no input file then take input from terminal
        // loop over each character from user input
        std::cout << "No Input File selected, please input to terminal: " << std::endl; //tells you that you didn't input a file so must input on terminal
        while (std::cin >> inputChar) {
            // Uppercase alphabetic characters
            inputText += transformChar(inputChar);  //transforms text to uppercase and makes numbers into letters (spelt out name)
            // If the character isn't alphabetic or numeric, DONT add it
        } 
        if(encrypt or decrypt) {    //same as above run encryption or decyrption if specified 
            inputText = runCaesarCipher(inputText,key,encrypt,decrypt);
        }
        inputText += "\n";  // appends a new line to the end of the user input 
    }

    // Print out the transliterated text
    if (!outputFile.empty()) {  // if there is an output file specified
        std::ofstream out_file{outputFile}; //creates an out stream from specified output file in cmd line arguments
        bool printoutok = out_file.good();  //creates a bool which checks if we can output to file
        if(printoutok){ //if we can output to file
            out_file << inputText;  //write text to file
        } else {    //if cant output to file
            std::cerr << "[Warning] cannot output to file ('" << outputFile //if cant output to file the return non zero value
                      << "')\n";
            return 1;
        }
    } else {    //if no output specified print to terminal
        std::cout << "Output file not specified, outputting to terminal: " << std::endl;
        std::cout << inputText;
    }
    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}