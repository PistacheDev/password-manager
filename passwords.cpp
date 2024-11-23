#include "header.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem; // Shortcut.

void createPassword(std::string account) // Create password function.
{
    if (!fs::exists(account + "/"))
        fs::create_directory(account); // Create the user's personnal directory if it's missing.

    std::string name;
    std::cout << "Password's mame (example: Google): ";
    std::cin >> name;

    if (fs::exists(account + "/" + name + ".md")) // If the password already exists.
    {
        std::string confirmation;
        std::cout << "This password already exists!\nDo you want to overwrite the current data? (y/n) ";
        std::cin >> confirmation; // Input.

        if (confirmation != "y")
        {
            std::cout << "Aborted!" << std::endl;
            return;
        };
    };

    std::string password;
    std::cout << "Password: ";
    std::cin >> password; // Input.
    std::string encoded = encode(password); // Encode the password with base64.
    std::ofstream file(account + "/" + name + ".md"); // Create the file.

    if (file.is_open()) // Check if the file is successfully created and opened.
    {
        file << encoded; // Write the encoded password into the file.
        file.close();
        std::cout << "The password called \"" << name << "\" has been created successfully!" << std::endl;
    }
    else
        std::cout << "Password's creation failed!" << std::endl;
};

void showPassword(std::string account) // Show password function.
{
    if (!fs::exists(account + "/")) // If the user's personnal folder doesn't exist.
    {
        std::cout << "There isn't any password available for this account!" << std::endl;
        return;
    };

    std::string password;
    std::cout << "Password to show: ";
    std::cin >> password; // Input.

    if (fs::exists(account + "/" + password + ".md"))
    {
        std::string content;
        std::ifstream file(account + "/" + password + ".md"); // Open the file in read-only mode.
        std::getline(file, content); // Get the file's content.
        file.close();
        std::string decoded = decode(content); // Decode the password using base64.
        std::cout << "Password " << password << " : " << decoded << "." << std::endl;
    }
    else
        std::cout << "This password doesn't exist!" << std::endl;
};

void removePassword(std::string account) // Delete password function.
{
    if (!fs::exists(account + "/")) // If the user's personnal folder doesn't exist.
    {
        std::cout << "This account doesn't have any password!";
        return;
    };

    std::string password;
    std::cout << "Password to delete: ";
    std::cin >> password; // Input.

    if (fs::exists(account + "/" + password + ".md")) // If the file exists.
    {
        fs::remove(account + "/" + password + ".md"); // Delete the file.
        std::cout << "Password removed successfully!" << std::endl;
    }
    else
        std::cout << "This password doesn't exist!" << std::endl;
};