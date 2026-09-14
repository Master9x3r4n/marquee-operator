#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>

#include "header/marquee.h"
#include "header/text.h"
#include "header/commands.h"

#define HEIGHT 7

int main() 
{
    std::vector<std::array<std::string, 7>> characters = initializeFont();

    bool isProgramRunning = true;
    std::string input = "";
    std::string marqueeText = "CSOPESY";
    bool isMarqueeRunning = false;
    int refreshSpeed = 0;
    
    while (isProgramRunning)
    {
        printMarquee(characters, marqueeText);
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
}