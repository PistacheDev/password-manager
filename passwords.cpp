#include "header.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

using namespace std;

void createPassword(string account)
{
    if (!filesystem::exists(account + "/")) filesystem::create_directory(account); // Create the user's personnal directory.
    string name;
    cout << "Password's name (example: Google): ";
    cin >> name;

    if (filesystem::exists(account + "/" + name + ".md")) // If the password already exists.
    {
        string confirmation;
        cout << "This password already exists!\nDo you want to overwrite it? (y/n) ";
        cin >> confirmation;

        if (confirmation != "y")
        {
            cout << "Aborted!" << endl;
            return;
        };
    };

    string password;
    cout << "Password: ";
    cin >> password;
    string encoded = encode(password); // Encode the password with base64.
    ofstream file(account + "/" + name + ".md"); // Create the file.

    if (file.is_open())
    {
        file << encoded; // Write the encoded password into the file.
        file.close();
        cout << "The password \"" << name << "\" has been created successfully!" << endl;
    }
    else cout << "The file's creation failed!" << endl;
};

void showPassword(string account)
{
    if (!filesystem::exists(account + "/") || isEmptyFolder(account + "/"))
    {
        cout << "There isn't any password available for this account!";
        return;
    };

    bool first = true;
    cout << "Available passwords: ";

    for (const auto & file : filesystem::directory_iterator(account + "/")) // List each available password.
    {
        filesystem::path path(file);
        if (!first) cout << ", " << path.stem();
        else cout << path.stem();
        first = false;
    };

    string password;
    cout << ".\nPassword to show: ";
    cin >> password;

    if (filesystem::exists(account + "/" + password + ".md"))
    {
        string content;
        ifstream file(account + "/" + password + ".md"); // Open the file in read-only mode.
        getline(file, content); // Get the file's content.
        file.close();
        string decoded = decode(content); // Decode the password using base64.
        cout << "Password \"" << password << "\": " << decoded << "." << endl;
    }
    else cout << "This password doesn't exist!" << endl;
};

void removePassword(string account)
{
    if (!filesystem::exists(account + "/") || isEmptyFolder(account + "/"))
    {
        cout << "This account doesn't have any password!";
        return;
    };

    bool first = true;
    cout << "Available passwords: ";

    for (const auto & file : filesystem::directory_iterator(account + "/")) // List each available password.
    {
        filesystem::path path(file);
        if (!first) cout << ", " << path.stem();
        else cout << path.stem();
        first = false;
    };

    string password;
    cout << ".\nPassword to delete: ";
    cin >> password;

    if (filesystem::exists(account + "/" + password + ".md")) // If the file exists.
    {
        string confirmation;
        cout << "Are you sure that you want to delete this password? (y/n) ";
        cin >> confirmation;

        if (confirmation != "y")
        {
            cout << "Aborted!" << endl;
            return;
        };

        filesystem::remove(account + "/" + password + ".md"); // Delete the file.
        cout << "Password deleted successfully!" << endl;
    }
    else cout << "This password doesn't exist!" << endl;
};