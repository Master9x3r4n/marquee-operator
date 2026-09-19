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
Compile and run the program using 
```
g++ -Wall -static -std=c++17 -o main.exe main.cpp helpers/marquee.cpp helpers/text.cpp helpers/commands.cpp
main.exe
```
Or run using batch file
```
run
```

## Credits
Fonts obtained from https://patorjk.com/software/taag/
