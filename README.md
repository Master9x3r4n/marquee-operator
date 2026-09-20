# OS MARQUEE OPERATOR
- Claro, Stephen Jakobb

This project contains a simple OS Emulator with a display output and command input. The main menu console consists of a scrolling ascii graphic marquee "animation" and Acceot commands to change the behavior of the text marquee. 
The following are the eligible commands to use:
- help - displays the commands and its description
- start_marquee - starts the marquee "animation"
- stop_marquee - stops the marquee "animation"
- set_text <text> - accepts a text input and displays it as a marquee
- set_speed <speed> - sets the marquee animation refresh in milliseconds
- exit - terminate the console

This project was developed using **C++** and implements threading for the rotating marquee functionality.

## Usage
Requires CMake 3.16+ and a C++17 compiler (g++, clang, or MSVC).

Configure and build
```
cmake -S . -B build
cmake --build build
```
If you are using MinGW on Windows, add `-G "MinGW Makefiles"` to the first command.

Then build and run in one step using
```
cmake --build build --target run
```
Or run the executable manually from inside the build folder
```
cd build
os_marquee        # ./os_marquee on Linux/macOS
```
The program loads `helpers/text/ascii_font.txt` relative to the working directory, and the build copies it next to the executable, so run it from the folder containing the executable (with Visual Studio's generator this is `build\Debug`).

## Credits
Fonts obtained from https://patorjk.com/software/taag/