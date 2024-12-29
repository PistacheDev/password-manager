#include "header.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void passwordGenerator()
{
    string lengthStr;
    cout << "We recommend you to generate a password with at least 12 characters inside it." << endl;
    cout << "Password length: ";
    cin >> lengthStr;

    if (!isNumber(lengthStr))
    {
        cout << "Please, enter a number!" << endl;
        clearTerminal();
        return;
    };

    int length = stoi(lengthStr);

    if (length < 1 || length > 1000)
    {
        cout << "The length must be between 1 and 1000 characters!";
        return;
    };

    string password;
    string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890~!@#$%^&*()_+-=[]{};:'\"\\|,<.>/?`";
    srand(time(0));

    for (int i = 0; i < length; i++)
    {
        int random = rand() % characters.length();
        password += characters[random];
    };

    cout << "Generated password: " << password;
};