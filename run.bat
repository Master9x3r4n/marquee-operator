@echo off
g++ -Wall -static -std=c++17 -o main.exe main.cpp helpers/marquee.cpp helpers/text.cpp helpers/commands.cpp
if errorlevel 1 exit /b %errorlevel%
main.exe