#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

void view_help() {
    std::cout << "help - displays the commands and its description\n";
    std::cout << "start_marquee - starts the marquee \"animation\"\n";
    std::cout << "stop_marquee - stops the marquee \"animation\"\n";
    std::cout << "set_text <text> - accepts a text input and displays it as a marquee\n";
    std::cout << "set_speed <speed> - sets the marquee animation refresh in milliseconds\n";
    std::cout << "exit - terminate the console\n";
}

void set_text(std::string& marqueeText, std::vector<std::string> args) {
    if (args.size() < 2)
        std::cout << "Invalid arguments. Usage: set_text <text>. Use \"help\" for more information\n";
    else {
        std::string text = "";
        for (unsigned int i = 1; i < args.size(); i++) {
            text = text + args[i];

            if (i+1 < args.size())
                text = text + " ";
        }

        marqueeText = text;
    }
}

void set_speed(int& refreshSpeed, std::vector<std::string> args) {
    if (args.size() != 1)
        std::cout << "Invalid arguments. Usage: set_speed <text>. Use \"help\" for more information\n";
    else
        refreshSpeed = std::stoi(args[1]);
}