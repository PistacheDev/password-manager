@echo off
:: Build from Windows for Linux.
x86_64-linux-gnu-g++ -std=c++17 -o pwd main.cpp encryptor.cpp tools.cpp accounts.cpp passwords.cpp generator.cpp
pause