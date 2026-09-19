@echo off
g++ -Wall -static -std=c++17 -o main.exe main.cpp header/marquee.cpp header/text.cpp header/commands.cpp
if errorlevel 1 exit /b %errorlevel%
main.exe