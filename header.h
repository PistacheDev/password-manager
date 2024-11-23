#ifndef HEADER_H
#define HEADER_H

#include <string>

std::string encode(const std::string input);
std::string decode(const std::string input);
bool isNumber(const std::string input);
bool hasInvalidCharacters(const std::string input);
void clearTerminal();
std::string loginAccount();
std::string createAccount();
std::string deleteAccount(const std::string account);
std::string editAccountPassword(const std::string account);
void createPassword(const std::string account);
void removePassword(const std::string account);
void showPassword(const std::string account);

#endif