#include <iostream>
#include <string>
#include "TransformChar.hpp"

std::string transformChar(const char in_Char)   //can be defined after main and then recalled at the start like in fortran
{
    /*  Takes an alphanumerical input character, converts to letters for any numerical input, and returns capitalised input 

        const char in_Char: input character

        return: The capitalised input character/string  
    */
    std::string in_Text{""};

    if (std::isalpha(in_Char)) {
            in_Text += std::toupper(in_Char);
            return in_Text;
        }

        // Transliterate digits to English words
    switch (in_Char) {
        case '0':
            in_Text += "ZERO";
            break;
        case '1':
            in_Text += "ONE";
            break;
        case '2':
            in_Text += "TWO";
            break;
        case '3':
            in_Text += "THREE";
            break;
        case '4':
            in_Text += "FOUR";
            break;
        case '5':
            in_Text += "FIVE";
            break;
        case '6':
            in_Text += "SIX";
            break;
        case '7':
            in_Text += "SEVEN";
            break;
        case '8':
            in_Text += "EIGHT";
            break;
        case '9':
            in_Text += "NINE";
            break;
    }

    return in_Text;

}
