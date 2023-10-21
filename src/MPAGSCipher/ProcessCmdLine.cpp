#include <iostream>
#include <vector>
#include <string>

#include "ProcessCmdLine.hpp"

bool processCmdLine(const std::vector<std::string>& args,
                    bool& helpRequested,
                    bool& versionRequested,
                    std::string& inputFileName,
                    std::string& outputFileName,
                    bool& encrypt,
                    bool& decrypt,
                    bool& keySupplied,
                    int& key)
{   
    /*
        processes the command line arguments which follow the name of the program e.g. --help 

        const std::vector<std::string>& args: input constant vector array which contains all of the command line arguments. 
        bool& helpRequested: input boolean of if help has been requested in the command line arguments
        bool& versionRequested: input boolean of if version has been requested in command line arguments
        std::string& inputFileName: input file name from the command line arguments
        std::string& outputFileName: output file name from the command line arguments
        bool& encrypt: encryption conditional
        bool& decrypt: decryption conditional
        bool& keySupplied: key conditional
        int& key: key value

        return: 0 if no errors, 1 if error with command line argument processing. 
                Edits the helpRequested, versionRequested, inputFileName, outputFileName, encrypt, decrypt and keySupplied variables
    */

    const std::size_t nCmdLineArgs{args.size()};    //calcualtes the size of the args vector

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) 
    {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
            break;
        } else if (args[i] == "--version") {
            versionRequested = true;
            break;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = args[i + 1];
                ++i;
            }
        } else if(args[i] == "--encrypt") { //if encryption is specified
            if(!decrypt) {  //check is not also asking for decryption
                if(i == nCmdLineArgs - 1) { //also check if this is the last argument as we require a key
                    if(keySupplied){
                        encrypt = true; //if key already supplied, fine
                    } else {
                        std::cerr << "[error] requires key argument to follow"  //if not and last element require key to be given
                                << std::endl;
                        return false;
                    }
                } else if (i != nCmdLineArgs - 1 and !keySupplied){
                    for(std::size_t j{i};j<nCmdLineArgs;j++){   //if not the last element and no key supplied yet
                        if(args[j]=="--key"){   //loop through all other remaining elements
                            keySupplied = true; //if there is a key, make keySupplied element true and allow encryption
                            encrypt = true;
                            continue;   //stop looking after this
                        } 
                    }
                    if(keySupplied){    //if keySupplied is true then good
                        encrypt = true;
                    } else {    //if we didnt find a key in the remaining elements of the arguments then give non zero return
                        std::cerr << "[error] requires key argument to follow"
                                << std::endl;
                        return false;
                    }
                }
            } else {    //makes sure that we can't use encrypt and decrypt simultaneously 
                std::cerr << "[error] --encrypt and --decrypt cannot not be used simultaneously"
                          << std::endl;
                return false;
            }
        } else if(args[i] == "--decrypt") { //much like encrypt above but for decrypt 
            if(!encrypt) {
                if(i == nCmdLineArgs - 1) {
                    if(keySupplied){
                        decrypt = true;
                    } else {
                        std::cerr << "[error] requires key argument to follow"
                                << std::endl;
                        return false;
                    }
                } else {
                    for(std::size_t j{i};j<nCmdLineArgs;j++){
                        if(args[j]=="--key"){
                            keySupplied = true;
                            decrypt = true;
                            continue;
                        } 
                    }
                    if(keySupplied){
                        decrypt = true;
                    } else {
                        std::cerr << "[error] requires key argument to follow"
                                << std::endl;
                        return false;
                    }
                }
            } else {
                std::cerr << "[error] --encrypt and --decrypt cannot not be used simultaneously"
                            << std::endl;
                return false;
            }
        } else if (args[i] == "--key") {    //checks for key
            if (i == nCmdLineArgs - 1) {    //if we have --key as k=last argument it means we are missing a key value
                std::cerr << "[error] --key requires an positive integer argument"  //give error in this scenario
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {    //if not last element then we can continue
                if (stoi(args[i+1]) >= 0){  //makes sure key is not negative 
                    keySupplied = true; //assigns correct key and suppiled check values
                    key = stoi(args[i+1]);
                    ++i; //skips key value so we dont double count accidentally
                } else {    //missing key value
                  std::cerr << "[error] --key requires an positive integer argument"
                            << std::endl;
                    // exit main with non-zero return to indicate failure
                    return false;  
                }
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i]
                      << "'\n";
            return false;
        }
    }
    
    return true;
}
