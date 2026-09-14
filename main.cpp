#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
using namespace std;

#include "header/marquee.h"
#include "header/text.h"
#include "header/commands.h"

#define HEIGHT 7

int main() 
{
    vector<array<string, 7>> characters = initializeFont();

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
            cout << "Error. Unknown command input.\n";
        }
    }
}