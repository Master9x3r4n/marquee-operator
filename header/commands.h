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

void command_interface(bool& isMarqueeRunning, std::string& marqueeText, int& refreshSpeed, bool& isProgramRunning) {
    std::string input = "";

    std::cout << "Group Developer:\n" << "Claro, Stephen Jakobb G.\n" << "Omandac, Karl Deejay\n\n"; 
    std::cout << "Command>";

    std::getline(std::cin, input);
    std::vector<std::string> args = getArgs(input);

    if (args[0] == "help")
    {
        view_help();
    }
    else if (args[0] == "start_marquee")
    {
        isMarqueeRunning = true;
    }        
    else if (args[0] == "stop_marquee")
    {
        isMarqueeRunning = false;
    }
    else if (args[0] == "set_text")
    {
        set_text(marqueeText, args);
    }
    else if (args[0] == "set_speed")
    {
        set_speed(refreshSpeed, args);
    }
    else if (args[0] == "exit")
    {
        isProgramRunning = false;
    }
    else
    {
        std::cout << "Error. Unknown command input.\n";
    }
}