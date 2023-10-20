#include <iostream>
#include <vector>
#include <string>

#include "ProcessCmdLine.hpp"

bool processCmdLine(const std::vector<std::string>& args,
                    bool& helpRequested,
                    bool& versionRequested,
                    std::string& inputFileName,
                    std::string& outputFileName)
{   
    /*
        processes the command line arguments which follow the name of the program e.g. --help 

        const std::vector<std::string>& args: input constant vector array which contains all of the command line arguments. 
        bool& helpRequested: input boolean of if help has been requested in the command line arguments
        bool& versionRequested: input boolean of if version has been requested in command line arguments
        std::string& inputFileName: input file name from the command line arguments
        std::string& outputFileName: output file name from the command line arguments

        return: 0 if no errors, 1 if error with command line argument processing. Edits the helpRequested, versionRequested, inputFileName and outputFileName variables
    */

    const std::size_t nCmdLineArgs{args.size()};

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
