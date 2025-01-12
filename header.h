#ifndef HEADER_H
#define HEADER_H

#include <string>
using namespace std;

string encode(const string input);
string decode(const string input);
bool isNumber(const string input);
bool hasInvalidCharacters(const string input);
bool isEmptyFolder(const string path);
void clearTerminal();
string loginAccount();
string createAccount();
string deleteAccount(const string account);
string editAccountPassword(const string account);
void createPassword(const string account);
void removePassword(const string account);
void showPassword(const string account);
void passwordGenerator();

#endif