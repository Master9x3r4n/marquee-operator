#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
using namespace std;

#include "header/marquee.h"
#include "header/text.h"

#define HEIGHT 7

int main() 
{
    vector<array<string, 7>> characters = initializeFont();

    // std::cout << "Loaded " << characters.size() << " group(s) of 7 lines.\n\n";
    // for (size_t i = 0; i < 10; i++) {
    //     std::cout << "--- Group " << i << " ---\n";
    //     for (size_t j = 0; j < characters[i].size(); j++) {
    //         std::cout << characters[i][j] << "]\n";
    //     }
    //     std::cout << "\n";
    // }
    // return 0;

    bool isProgramRunning = true;
    string input = "";
    string marqueeText = "CSOPESY";
    bool isMarqueeRunning = false;
    int refreshSpeed = 0;
    
    while (isProgramRunning)
    {
        printMarquee(characters, marqueeText);
        cout << "Group Developer:\n" << "Claro, Stephen Jakobb G.\n" << "Omandac, Karl Deejay\n\n";
    
        cout << "Command>";

        getline(cin, input);
        vector<string> args = getArgs(input);

        if (args[0] == "help")
        {
            cout << "help - displays the commands and its description\n";
            cout << "start_marquee - starts the marquee \"animation\"\n";
            cout << "stop_marquee - stops the marquee \"animation\"\n";
            cout << "set_text <text> - accepts a text input and displays it as a marquee\n";
            cout << "set_speed <speed> - sets the marquee animation refresh in milliseconds\n";
            cout << "exit - terminate the console\n";
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
            if (args.size() < 2)
                cout << "Invalid arguments. Usage: set_text <text>. Use \"help\" for more information\n";
            else
                marqueeText = args[1];
        }
        else if (args[0] == "set_speed")
        {
            if (args.size() < 2)
                cout << "Invalid arguments. Usage: set_text <text>. Use \"help\" for more information\n";
            else
                refreshSpeed = stoi(args[1]);
        }
        else if (args[0] == "exit")
        {
            isProgramRunning = false;
        }
        else
        {
            cout << "Error. Unknown command input.\n";
        }
        
    }

}