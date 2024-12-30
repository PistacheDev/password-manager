@echo off
:: Build from Windows for Windows.
g++ -std=c++17 -o ../pwd.exe ../main.cpp ../encryptor.cpp ../tools.cpp ../accounts.cpp ../passwords.cpp ../generator.cpp
pause