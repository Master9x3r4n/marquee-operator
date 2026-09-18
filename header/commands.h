#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>

void viewHelp() {
    const int colWidth = 24;

    std::cout << "USAGE:\n"
              << "  <command> [arguments]\n\n"
              << "COMMANDS:\n"
              << "  " << std::left << std::setw(colWidth) << "help"              << "Displays list of commands and descriptions\n"
              << "  " << std::left << std::setw(colWidth) << "start_marquee"      << "Starts the marquee animation\n"
              << "  " << std::left << std::setw(colWidth) << "stop_marquee"       << "Stops the marquee animation\n"
              << "  " << std::left << std::setw(colWidth) << "set_text <text>"    << "Sets text input to display in the marquee\n"
              << "  " << std::left << std::setw(colWidth) << "set_speed <speed>"  << "Sets animation refresh speed in milliseconds\n"
              << "  " << std::left << std::setw(colWidth) << "exit"             << "Terminate the console\n\n";
}

void setText(Marquee& marquee, std::vector<std::string> args) {
    if (args.size() < 2)
        std::cout << "Invalid arguments. Usage: set_text <text>. Use \"help\" for more information\n";
    else {
        std::string text = "";
        for (unsigned int i = 1; i < args.size(); i++) {
            text = text + args[i];

            if (i+1 < args.size())
                text = text + " ";
        }

        marquee.setText(text);
    }
}

void setSpeed(Marquee& marquee, std::vector<std::string> args) {
    if (args.size() != 1)
        std::cout << "Invalid arguments. Usage: set_speed <text>. Use \"help\" for more information\n";
    else
        marquee.setSpeed(std::stoi(args[1]));
}

void displayDefault(Marquee marquee, bool show = true)
{
    marquee.printMarquee();
    if (show)
        std::cout << "Developer:\n" << "Claro, Stephen Jakobb G.\n\n"; 
}

void commandInterface(bool& isProgramRunning, 
                       bool& isMarqueeRunning, 
                       Marquee& marquee
                    ) 
{
    std::string input = "";
    std::cout << "Command>";

    std::getline(std::cin, input);
    std::vector<std::string> args = getArgs(input);

    if (args[0] == "help")
    {
        displayDefault(marquee, false);
        viewHelp();
    }
    else if (args[0] == "start_marquee")
    {
        isMarqueeRunning = true;
        displayDefault(marquee);
    }        
    else if (args[0] == "stop_marquee")
    {
        isMarqueeRunning = false;
        displayDefault(marquee);
    }
    else if (args[0] == "set_text")
    {
        setText(marquee, args);
        displayDefault(marquee);
    }
    else if (args[0] == "set_speed")
    {
        setSpeed(marquee, args);
        displayDefault(marquee);
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