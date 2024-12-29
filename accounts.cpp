#include "header.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

string loginAccount()
{
    if (!filesystem::exists("accounts/") || isEmptyFolder("accounts/"))
    {
        cout << "There isn't any account available!";
        return "null";
    };

    bool first = true;
    cout << "Available accounts: ";

    for (const auto & file : filesystem::directory_iterator("accounts/")) // List each available account.
    {
        filesystem::path path(file);
        if (!first) cout << ", " << path.stem();
        else cout << path.stem();
        first = false;
    };

    string account;
    cout << ".\nUsername: ";
    cin >> account;

    if (!filesystem::exists("accounts/" + account + ".md"))
    {
        cout << "This account doesn't exist!";
        return "null";
    };

    string password;
    cout << "Password: ";
    cin >> password;
    ifstream file("accounts/" + account + ".md");

    if (file.is_open())
    {
        string content;
        getline(file, content); // Read the file's content.
        file.close();
        string decoded = decode(content); // Decode the password using base64.

        if (password == decoded)
        {
            cout << "Successfully connected!";
            return account; // Access granted.
        };

        cout << "Incorrect password!";
        return "null";
    };

    cout << "Impossible to log into this account!";
    return "null";
};

string createAccount()
{
    if (!filesystem::exists("accounts")) filesystem::create_directory("accounts"); // Create the accounts folder.
    string account;
    int loop = 0; // Max attempts.
    bool success = false;

    while (loop < 10)
    {
        loop++;
        cout << "Username: ";
        cin >> account;

        if (hasInvalidCharacters(account) || account == "null")
            cout << "Please, enter a valid name!";
        else if (filesystem::exists("accounts/" + account + ".md"))
            cout << "This account already exists!";
        else
        {
            success = true;
            break; // Break the loop to continue.
        };
    };

    if (!success)
    {
        cout << "Too many fails!\nPress [Enter] to close the program..";
        return "null";
    };

    string password;
    cout << "Password: ";
    cin >> password;
    string encoded = encode(password); // Encode the password with base64.
    ofstream file("accounts/" + account + ".md"); // Create the account's file.

    if (file.is_open())
    {
        file << encoded; // Write the encoded password into the file.
        file.close();
        cout << "Account created successfully!";
        return account; // Automatically log in the user.
    };

    cout << "The account creation failed!";
    return "null";
};

string deleteAccount(string account)
{
    cout << "Warning! The account's suppression is definitive!" << endl;
    cout << "Are you sure that you want to proceed? (y/n) ";
    string confirmation;
    cin >> confirmation;

    if (confirmation == "y")
    {
        if (filesystem::exists("accounts/" + account + ".md")) filesystem::remove("accounts/" + account + ".md"); // Delete the account's file.
        if (filesystem::exists(account + "/")) filesystem::remove_all(account + "/"); // Delete every user's passwords.
        cout << "Account deleted successfully!";
        return "null"; // Log out the user.
    };

    cout << "Aborted!";
    return account; // Stay logged in.
};

string editAccountPassword(string account)
{
    if (!filesystem::exists("accounts/" + account + ".md"))
    {
        cout << "This account no longer exists!";
        return "null"; // Log out the user.
    };

    string current;
    cout << "Current password: ";
    cin >> current;
    ifstream file("accounts/" + account + ".md"); // Open the file in read-only mode.

    if (file.is_open())
    {
        string content;
        getline(file, content); // Get the file's content.
        file.close();
        string decoded = decode(content); // Decode the password using base64.

        if (current == decoded)
        {
            string newPassword;
            cout << "New password: ";
            cin >> newPassword;
            string encoded = encode(newPassword); // Encode the password with base64.
            ofstream file("accounts/" + account + ".md");

            if (file.is_open())
            {
                file << encoded; // Write the new password into the file.
                cout << "Password modified successfully!";
            }
            else cout << "The password modification failed!";
            return account; // Stay logged in.
        };

        cout << "Incorrect password!";
        return "null"; // Log out the user for security reasons.
    };

    cout << "The password verification failed!";
    return account; // Stay logged in.
};