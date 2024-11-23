#include "header.h"
#include <string>
#include <regex>
#include <iostream>

bool isNumber(std::string input) // Check if the input string is a number.
{
    for (char const &character : input) // Check if each character is a digit or noy.
        if (!std::isdigit(character))
            return false; // If any of the character isn't a digit, it's not a number.

    return true;
};

bool hasInvalidCharacters(std::string input) // Check if the input has any invalid charcter.
{
    std::regex invalid("[\\\\/:*?\"<>|]"); // Define what characters are invalud.
    return std::regex_search(input, invalid); // Return true if any invalid character is found in the input.
};

void clearTerminal()
{
    std::cout << "\nPress [Enter] to continue.. ";
    std::cin.ignore();
    std::cin.ignore();

    #ifdef _WIN32 // If we're running on Windows.
        system("cls");
    #else // Linux or MacOS.
        system("clear");
    #endif
};