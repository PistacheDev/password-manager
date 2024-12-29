#include "header.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string loggedIn = "null"; // Connection state (null = not connected to any account).

    while (true)
    {
        cout << "An Open Source password manager.\nGitHub repository: https://github.com/PistacheDev/password-manager." << endl;

        if (loggedIn == "null") // If the user isn't logged in.
        {
            string option;
            cout << "\nAvailable options:\n1) Log in.\n2) Create an account.\n3) Close the program.\n\nChoice: ";
            cin >> option;

            if (!isNumber(option))
            {
                cout << "Please, enter a number!";
                clearTerminal();
                continue;
            };

            switch (stoi(option))
            {
                case 1: // Log in.
                    loggedIn = loginAccount();
                    break;
                case 2: // Create an account.
                    loggedIn = createAccount();
                    break;
                case 3: // Close the program.
                    cout << "Bye!" << endl;
                    exit(0);
                    break;
                default:
                    cout << "This option doesn't exist or isn't available at this point of time!";
                    break;
            };
        }
        else
        {
            string option;
            cout << "Logged in as: " << loggedIn << "." << endl;
            cout << "\nAvailable options:\n1) Create a password.\n2) Show a password.\n3) Remove a password.\n4) Generate a password.\n5) Log out.\n6) Edit the account's password.\n7) Delete the account.\n8) Close the program.\n\nChoice: ";
            cin >> option;

            if (!isNumber(option))
            {
                cout << "Please, enter a number!";
                clearTerminal();
                continue;
            };

            switch (stoi(option))
            {
                case 1: // Create a password.
                    createPassword(loggedIn);
                    break;
                case 2: // Show a password.
                    showPassword(loggedIn);
                    break;
                case 3: // Remove a password.
                    removePassword(loggedIn);
                    break;
                case 4: // Generate a password.
                    passwordGenerator();
                    break;
                case 5: // Log out.
                    loggedIn = "null";
                    cout << "Logged out." << endl;
                    break;
                case 6: // Edit the account's password.
                    loggedIn = editAccountPassword(loggedIn);
                    break;
                case 7: // Delete the account.
                    loggedIn = deleteAccount(loggedIn);
                    break;
                case 8: // Close the program.
                    cout << "Bye!" << endl;
                    exit(0);
                    break;
                default:
                    cout << "This option doesn't exist or isn't available at this point of time!";
                    break;
            };
        };

        clearTerminal();
    };

    return -1;
};