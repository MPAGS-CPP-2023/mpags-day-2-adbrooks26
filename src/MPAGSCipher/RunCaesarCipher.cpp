#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "RunCaesarCipher.hpp"

std::string runCaesarCipher(const std::string& inputText, const std::size_t key, const bool encrypt, const bool decrypt){

    /*
        encrypts or decrypts an input string using a Caesar Cipher

        const std::string& inputText: input string which will be encrypted or decrypted
        const std::size_t key: the key to the Caesar Cipher
        const bool encrypt: encyrption condition
        const bool decrypt: decryption condition

        return: cipherOut -- string which has been encrypted or decrypted
    */

    //create the alphabet container and output string
    const std::vector<char> alphabet = {'A','B','C','D','E','F','G','H','I',
                                        'J','K','L','M','N','O','R','Q','R',
                                        'S','T','U','V','W','X','Y','Z'};
    std::string cipherOut{""};
    //initilaised some variables for use later
    char newChar{'a'};
    int indexpos{0};
    int remainder{0};


    //loop over each character in the text
    for(std::size_t i{0}; i < inputText.length();i++){

        for(std::size_t j{0}; j < alphabet.size();j++){ //checks each value in the input string against the alphabet container 
            if (inputText[i]==alphabet[j]){ //checks for match between character and alphabet letter
                indexpos = j;   //if match then assign the vector index to indexpos variable
                continue;   //exit loop as we don't need to do look anymore
            } 
        }

        if(encrypt){    //if we have specified encryption (we have prevented both from being specified in ProcessCmdLine.cpp file)
            indexpos = indexpos + key;  //encryption adds the key to the index
            if (indexpos <= 25 and indexpos >= 0){  //if this new index is inside the container limits then proceed as normal
                newChar = alphabet[indexpos];   //find new letter from index
                cipherOut += newChar;   //append to output 
            } else if(indexpos > 25) {  //if new index is outside limits of container 
                remainder = indexpos % 26;  //take the modulo of the index with the total length of the container
                indexpos = remainder;   //assign the remainder to be the index -- corrects for overflow of container
                newChar = alphabet[indexpos];   //find new letter
                cipherOut += newChar;   //append to output
            }
        } else if(decrypt) {    //if decryption specified
            indexpos = indexpos - key;  //decryption takes away the key from the index

            if (indexpos <= 25 and indexpos >= 0){  //if inside container limits continue as normal
                newChar = alphabet[indexpos];
                cipherOut += newChar;
            } else if(indexpos < 0) {   //if outside container limits
                indexpos = -indexpos;   //decryption will typically make negative indexes so we correct for this
                remainder = indexpos % 26;  //take modulo with container range
                indexpos = 26 - remainder;  //now subtract the remainder from 26 to get to new letter
                newChar = alphabet[indexpos];
                cipherOut += newChar;
            } 
        }
    }
    return cipherOut;      // returns the output string
}