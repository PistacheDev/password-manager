#include "header.h"
#include <string>
#include <regex>
#include <iostream>
#include <filesystem>

using namespace std;

bool isNumber(string input)
{
    for (char const &character : input)
        if (!isdigit(character))
            return false;

    return true;
};

bool hasInvalidCharacters(string input)
{
    regex invalid("[\\\\/:*?\"<>|]"); // Invalid characters.
    return regex_search(input, invalid);
};

bool isEmptyFolder(const std::string path)
{
    return filesystem::is_directory(path) && filesystem::directory_iterator(path) == filesystem::directory_iterator(); // Check if the folder is empty or not.
};

void clearTerminal()
{
    cout << "\nPress [Enter] to continue.. ";
    cin.ignore();
    cin.ignore();

    #ifdef _WIN32 // Windows.
        system("cls");
    #else // Linux or MacOS.
        system("clear");
    #endif
};