#include "header.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem; // Shortcut.

std::string loginAccount() // Log in function.
{
    std::string account;
    std::cout << "Account's name: ";
    std::cin >> account; // Input.

    if (!fs::exists("accounts/" + account + ".md")) // Check if the account exists.
    {
        std::cout << "This account doesn't exist!" << std::endl;
        return "null";
    };

    std::string password;
    std::cout << "Password: ";
    std::cin >> password; // Input.
    std::ifstream file("accounts/" + account + ".md");

    if (file.is_open()) // Check if the file exists and is opened.
    {
        std::string content;
        std::getline(file, content); // Read the file's content.
        file.close(); // Close it.
        std::string decoded = decode(content); // Decode the password using base64.

        if (password == decoded) // If the two passwords match.
        {
            std::cout << "Successfully connected!" << std::endl;
            return account; // Log in.
        }
        else
        {
            std::cout << "Incorrect password!" << std::endl;
            return "null";
        };
    }
    else
    {
        std::cout << "Impossible to connect to this account!" << std::endl;
        return "null";
    };
};

std::string createAccount() // Create account function.
{
    if (!fs::exists("accounts"))
        fs::create_directory("accounts"); // Create the accounts folder if it's missing.

    std::string account;
    int loop = 0; // Max attempts.
    bool success = false;

    while (loop < 10)
    {
        loop++;
        std::cout << "Account's name: ";
        std::cin >> account; // Input.

        if (hasInvalidCharacters(account)) // Check if the input contains any invalid character.
            std::cout << "Please, enter a valid name!\n" << std::endl;
        else if (fs::exists("accounts/" + account + ".md")) // Check if the account already exists.
            std::cout << "This account already exists!\n" << std::endl;
        else
        {
            success = true;
            break; // Break the loop to continue.
        };
    };

    if (!success)
    {
        std::cout << "Too many fails!\nPress [Enter] to close the program..";
        return "null";
    };

    std::string password;
    std::cout << "Password: ";
    std::cin >> password; // Input.
    std::string encoded = encode(password); // Encode the password with base64.
    std::ofstream file("accounts/" + account + ".md"); // Create the file.

    if (file.is_open()) // If the file is successfully created and opened.
    {
        file << encoded; // Write the encoded password into the file.
        file.close();
        std::cout << "Account created successfully!" << std::endl;
        return account; // Automatically log in the user after the account's creation.
    }
    else
    {
        std::cout << "Impossible to create the account!" << std::endl;
        return "null";
    };
};

std::string deleteAccount(std::string account) // Delete account function.
{
    std::cout << "The account's suppression is definitive!" << std::endl;
    std::cout << "Are you sure that you want to proceed (y/n) ? ";
    std::string confirmation;
    std::cin >> confirmation; // Input.

    if (confirmation == "y") // User's confirmation.
    {
        if (fs::exists("accounts/" + account + ".md"))
            fs::remove("accounts/" + account + ".md"); // Delete the account's file.
        else
        {
            std::cout << "Impossible to delete the account because it doesn't exist!" << std::endl;
            return account;
        };

        if (fs::exists(account + "/"))
            fs::remove_all(account + "/"); // Delete every user's passwords.

        std::cout << "Account deleted successfully!" << std::endl;
        return "null"; // Log out the user.
    }
    else
    {
        std::cout << "Aborted!" << std::endl;
        return account; // Maintain the connection.
    };
};

std::string editAccountPassword(std::string account) // Edit account's password function.
{
    if (!fs::exists("accounts/" + account + ".md"))
    {
        std::cout << "This account no longer exists!" << std::endl;
        return "null"; // Log out the user.
    };

    std::string current;
    std::cout << "Current password: ";
    std::cin >> current; // Input.
    std::ifstream file("accounts/" + account + ".md"); // Open the file in read-only mode.

    if (file.is_open()) // Check if the file is successfully opened.
    {
        std::string content;
        std::getline(file, content); // Get the file's content.
        file.close();
        std::string decoded = decode(content); // Decode the password using base64.

        if (current == decoded) // If the two passwords match.
        {
            std::string newPassword;
            std::cout << "New password: ";
            std::cin >> newPassword; // Input.
            std::string encoded = encode(newPassword); // Encode the password with base64.
            std::ofstream file("accounts/" + account + ".md"); // Create the file.

            if (file.is_open()) // Check if the file is successfully created and opened.
            {
                file << encoded;
                std::cout << "Password edited successfully!" << std::endl;
            }
            else
                std::cout << "Password's modification failed!" << std::endl;

            return account; // Maintain the connection.
        }
        else
        {
            std::cout << "Incorrect password!" << std::endl;
            return "null"; // Log out the user for security reasons.
        };
    }
    else
    {
        std::cout << "The password's verification failed!" << std::endl;
        return account; // Maintain the connection.
    };
};