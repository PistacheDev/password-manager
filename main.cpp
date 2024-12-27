#include "header.h"
#include <iostream>
#include <string>

int main()
{
    std::string loggedIn = "null"; // Connection state (null = not connected to any account).

    while (true)
    {
        std::cout << "An Open Source password manager.\nGitHub repository: https://github.com/PistacheDev/password-manager." << std::endl;

        if (loggedIn == "null") // If the user isn't logged in.
        {
            std::string option;
            std::cout << "\nAvailable options:\n1) Log in.\n2) Create an account.\n3) Close the program.\n\nChoice: ";
            std::cin >> option;

            if (!isNumber(option))
            {
                std::cout << "Please, enter a number!" << std::endl;
                clearTerminal();
                continue;
            };

            switch (std::stoi(option))
            {
                case 1: // Log in.
                    loggedIn = loginAccount();
                    break;
                case 2: // Create an account.
                    loggedIn = createAccount();
                    break;
                case 3: // Close the program.
                    std::cout << "Bye!" << std::endl;
                    exit(0);
                    break;
                default:
                    std::cout << "This option doesn't exist or isn't available at this point of time!" << std::endl;
                    break;
            };
        }
        else
        {
            std::string option;
            std::cout << "Logged in as: " << loggedIn << "." << std::endl;
            std::cout << "\nAvailable options:\n1) Create a password.\n2) Show a password.\n3) Remove a password.\n4) Log out.\n5) Edit the account's password.\n6) Delete the account.\n7) Close the program.\n\nChoice: ";
            std::cin >> option;

            if (!isNumber(option))
            {
                std::cout << "Please, enter a number!" << std::endl;
                clearTerminal();
                continue;
            };

            switch (std::stoi(option))
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
                case 4: // Log out.
                    loggedIn = "null";
                    std::cout << "Logged out." << std::endl;
                    break;
                case 5: // Edit the account's password.
                    loggedIn = editAccountPassword(loggedIn);
                    break;
                case 6: // Delete the account.
                    loggedIn = deleteAccount(loggedIn);
                    break;
                case 7: // Close the program.
                    std::cout << "Bye!" << std::endl;
                    exit(0);
                    break;
                default:
                    std::cout << "This option doesn't exist or isn't available at this point of time!" << std::endl;
                    break;
            };
        };

        clearTerminal();
    };

    return -1;
};